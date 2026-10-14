// Minimal stand-in for nod (https://github.com/encounter/nod) for web builds,
// where the Rust library isn't available. Supports what aurora's DVD layer uses,
// for plain GameCube disc images (.iso/.gcm) only: the disc header, the data
// partition's boot/bi2/apploader/DOL/FST blobs, FST iteration, and file and
// whole-disc read handles. include/nod.h is nod's own C header.

#include <nod.h>

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

namespace {
std::string s_error;

uint32_t be32(const uint8_t* p) { return (uint32_t(p[0]) << 24) | (uint32_t(p[1]) << 16) | (uint32_t(p[2]) << 8) | p[3]; }

struct Disc
{
    NodDiscStream stream{};
    uint64_t size = 0;
    std::vector<uint8_t> header;     // 0x000..0x440 (boot.bin)
    std::vector<uint8_t> bi2;        // 0x440..0x2440
    std::vector<uint8_t> apploader;
    std::vector<uint8_t> dol;
    std::vector<uint8_t> fst;
    int refs = 1; // disc handle + partition handles + file handles keep it alive

    bool read_at(uint64_t offset, void* out, size_t len)
    {
        auto* dst = static_cast<uint8_t*>(out);
        while (len > 0)
        {
            int64_t n = stream.read_at(stream.user_data, offset, dst, len);
            if (n <= 0)
                return false;
            dst += n;
            offset += (uint64_t)n;
            len -= (size_t)n;
        }
        return true;
    }

    bool read_vec(uint64_t offset, size_t len, std::vector<uint8_t>& out)
    {
        out.resize(len);
        return len == 0 || read_at(offset, out.data(), len);
    }

    void release()
    {
        if (--refs == 0)
        {
            if (stream.close)
                stream.close(stream.user_data);
            delete this;
        }
    }
};

// Size of a DOL from its header: max end of the 7 text + 11 data sections.
uint32_t dol_size(const uint8_t* hdr)
{
    uint32_t end = 0x100;
    for (int i = 0; i < 18; i++)
    {
        uint32_t off = be32(hdr + i * 4);
        uint32_t sz = be32(hdr + 0x90 + i * 4);
        if (off != 0 && sz != 0)
            end = std::max(end, off + sz);
    }
    return end;
}
} // namespace

enum class Kind
{
    Disc,
    Partition,
    File,
};

struct NodHandle
{
    Kind kind;
    Disc* disc;
    uint64_t base = 0; // file: absolute offset on disc
    uint64_t length = 0;
    uint64_t pos = 0;
    std::vector<uint8_t> buf; // nod_buf_read scratch
};

extern "C" {

const char* nod_error_message(void) { return s_error.c_str(); }

NodResult nod_disc_open(const char*, const NodDiscOptions*, NodHandle**)
{
    s_error = "nod_disc_open(path) is not supported in this build";
    return NOD_RESULT_ERR_OTHER;
}

NodResult nod_disc_open_stream(const NodDiscStream* stream, const NodDiscOptions*, NodHandle** out)
{
    *out = nullptr;
    auto* disc = new Disc;
    disc->stream = *stream;
    disc->size = stream->stream_len ? (uint64_t)stream->stream_len(stream->user_data) : 0;
    auto fail = [&](const char* msg, NodResult r) {
        s_error = msg;
        disc->release();
        return r;
    };
    if (!disc->read_vec(0, 0x440, disc->header) || !disc->read_vec(0x440, 0x2000, disc->bi2))
        return fail("couldn't read disc header", NOD_RESULT_ERR_IO);
    static const uint8_t gcn[4] = {0xC2, 0x33, 0x9F, 0x3D};
    if (memcmp(disc->header.data() + 0x1C, gcn, 4) != 0)
        return fail("not a GameCube disc image (only uncompressed .iso/.gcm are supported)", NOD_RESULT_ERR_FORMAT);

    uint8_t apploaderHdr[0x20];
    if (!disc->read_at(0x2440, apploaderHdr, sizeof(apploaderHdr)))
        return fail("couldn't read apploader", NOD_RESULT_ERR_IO);
    uint32_t apploaderSize = 0x20 + be32(apploaderHdr + 0x14) + be32(apploaderHdr + 0x18);
    if (!disc->read_vec(0x2440, apploaderSize, disc->apploader))
        return fail("couldn't read apploader", NOD_RESULT_ERR_IO);

    const uint8_t* boot = disc->header.data();
    uint32_t dolOffset = be32(boot + 0x420);
    uint32_t fstOffset = be32(boot + 0x424);
    uint32_t fstSize = be32(boot + 0x428);
    uint8_t dolHdr[0x100];
    if (!disc->read_at(dolOffset, dolHdr, sizeof(dolHdr)) || !disc->read_vec(dolOffset, dol_size(dolHdr), disc->dol))
        return fail("couldn't read main.dol", NOD_RESULT_ERR_IO);
    if (fstSize < 12 || !disc->read_vec(fstOffset, fstSize, disc->fst))
        return fail("couldn't read the file system table", NOD_RESULT_ERR_IO);

    *out = new NodHandle{Kind::Disc, disc, 0, disc->size};
    return NOD_RESULT_OK;
}

NodResult nod_disc_open_partition(NodHandle* disc, uint32_t index, const NodPartitionOptions*, NodHandle** out)
{
    if (disc == nullptr || disc->kind != Kind::Disc || index != 0)
        return NOD_RESULT_ERR_NOT_FOUND;
    disc->disc->refs++;
    *out = new NodHandle{Kind::Partition, disc->disc, 0, disc->disc->size};
    return NOD_RESULT_OK;
}

NodResult nod_disc_open_partition_kind(NodHandle* disc, uint32_t kind, const NodPartitionOptions* options, NodHandle** out)
{
    if (kind != NOD_PARTITION_KIND_DATA)
        return NOD_RESULT_ERR_NOT_FOUND;
    return nod_disc_open_partition(disc, 0, options, out);
}

NodResult nod_partition_open_file(NodHandle* partition, uint32_t fst_index, NodHandle** out)
{
    if (partition == nullptr || partition->kind != Kind::Partition)
        return NOD_RESULT_ERR_INVALID_HANDLE;
    const auto& fst = partition->disc->fst;
    uint32_t count = be32(fst.data() + 8);
    if (fst_index == 0 || fst_index >= count || (size_t)(fst_index + 1) * 12 > fst.size())
        return NOD_RESULT_ERR_NOT_FOUND;
    const uint8_t* e = fst.data() + fst_index * 12;
    if (e[0] != 0)
        return NOD_RESULT_ERR_NOT_FOUND; // directory
    partition->disc->refs++;
    *out = new NodHandle{Kind::File, partition->disc, be32(e + 4), be32(e + 8)};
    return NOD_RESULT_OK;
}

void nod_free(NodHandle* handle)
{
    if (handle == nullptr)
        return;
    handle->disc->release();
    delete handle;
}

int64_t nod_read(NodHandle* handle, uint8_t* buf, size_t len)
{
    if (handle == nullptr)
        return -1;
    if (handle->pos >= handle->length)
        return 0;
    len = (size_t)std::min<uint64_t>(len, handle->length - handle->pos);
    if (!handle->disc->read_at(handle->base + handle->pos, buf, len))
        return -1;
    handle->pos += len;
    return (int64_t)len;
}

// aurora's DVD layer asks where a file is, so the page can fetch a read's bytes first.
int64_t nod_web_file_disc_offset(const NodHandle* handle)
{
    return handle != nullptr && handle->kind == Kind::File ? (int64_t)handle->base : -1;
}

int64_t nod_seek(NodHandle* handle, int64_t offset, int32_t whence)
{
    if (handle == nullptr)
        return -1;
    int64_t pos;
    switch (whence)
    {
    case 0: pos = offset; break;
    case 1: pos = (int64_t)handle->pos + offset; break;
    case 2: pos = (int64_t)handle->length + offset; break;
    default: return -1;
    }
    if (pos < 0)
        return -1;
    handle->pos = (uint64_t)pos;
    return pos;
}

const void* nod_buf_read(NodHandle* handle, size_t* out_len)
{
    *out_len = 0;
    if (handle == nullptr || handle->pos >= handle->length)
        return nullptr;
    size_t len = (size_t)std::min<uint64_t>(0x8000, handle->length - handle->pos);
    handle->buf.resize(len);
    if (!handle->disc->read_at(handle->base + handle->pos, handle->buf.data(), len))
        return nullptr;
    *out_len = len;
    return handle->buf.data();
}

void nod_buf_consume(NodHandle* handle, size_t n)
{
    if (handle != nullptr)
        handle->pos += n;
}

NodResult nod_disc_header(const NodHandle* disc, NodDiscHeader* out)
{
    if (disc == nullptr)
        return NOD_RESULT_ERR_INVALID_HANDLE;
    static_assert(sizeof(NodDiscHeader) == 0x400);
    memcpy(out, disc->disc->header.data(), sizeof(NodDiscHeader));
    return NOD_RESULT_OK;
}

NodResult nod_disc_meta(const NodHandle* disc, NodDiscMeta* out)
{
    if (disc == nullptr)
        return NOD_RESULT_ERR_INVALID_HANDLE;
    *out = {};
    out->format = NOD_FORMAT_ISO;
    out->lossless = true;
    out->disc_size = disc->disc->size;
    return NOD_RESULT_OK;
}

uint64_t nod_disc_size(const NodHandle* disc) { return disc ? disc->disc->size : 0; }

size_t nod_disc_partitions(const NodHandle* disc, NodPartitionInfo* out, size_t cap)
{
    if (disc == nullptr)
        return 0;
    if (cap > 0)
        out[0] = {0, NOD_PARTITION_KIND_DATA, disc->disc->size};
    return 1;
}

bool nod_partition_is_wii(const NodHandle*) { return false; }

NodResult nod_partition_meta(const NodHandle* partition, NodPartitionMeta* out)
{
    if (partition == nullptr)
        return NOD_RESULT_ERR_INVALID_HANDLE;
    const Disc* d = partition->disc;
    *out = {};
    out->raw_boot = {d->header.data(), d->header.size()};
    out->raw_bi2 = {d->bi2.data(), d->bi2.size()};
    out->raw_apploader = {d->apploader.data(), d->apploader.size()};
    out->raw_dol = {d->dol.data(), d->dol.size()};
    out->raw_fst = {d->fst.data(), d->fst.size()};
    return NOD_RESULT_OK;
}

void nod_partition_iterate_fst(const NodHandle* partition, NodFstCallback callback, void* user_data)
{
    if (partition == nullptr)
        return;
    const auto& fst = partition->disc->fst;
    uint32_t count = be32(fst.data() + 8);
    if ((size_t)count * 12 > fst.size())
        return;
    const char* names = (const char*)fst.data() + count * 12;
    size_t namesLen = fst.size() - count * 12;
    uint32_t i = 1;
    while (i < count)
    {
        const uint8_t* e = fst.data() + i * 12;
        uint32_t nameOff = be32(e) & 0xFFFFFF;
        const char* name = nameOff < namesLen ? names + nameOff : "";
        bool isDir = e[0] != 0;
        uint32_t next = callback(i, isDir ? NOD_NODE_KIND_DIRECTORY : NOD_NODE_KIND_FILE, name, be32(e + 8), user_data);
        if (next == NOD_FST_STOP)
            break;
        i = next;
    }
}

uint32_t nod_partition_find_file(const NodHandle* partition, const char* path, NodNodeKind* out_kind, uint32_t* out_length)
{
    (void)partition;
    (void)path;
    (void)out_kind;
    (void)out_length;
    return UINT32_MAX; // unused by aurora
}

} // extern "C"
