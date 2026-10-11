#include "Unknown/File_0x800a64e0.h"
#include "Dolphin/os.h"


DataVars gDataDecompressorValues;

#define LZSS_FLAG_SIZE 1
#define LZSS_BYTE_SIZE 8
#define LZSS_MINIMUM_REPETITION_SIZE 2

/*================================================================================*/

#define STRUCT_OFFSET(structName, memberField) \
    (size_t)(&((structName *)NULL)->memberField)

/*================================================================================*/

void SetReadParameters(AssetLoadInstructions *instructions, void *pCompressedData, void *pOutData, BOOL readInSegments)
{
    uint segmentSize;

    gDataDecompressorValues.RepetitionSize = instructions->compressionConstants >> 8;
    gDataDecompressorValues.LookBackSize = instructions->compressionConstants & 0xff;
    gDataDecompressorValues.CachedBytesToRead = gDataDecompressorValues.BytesToRead = instructions->originalDiskSize;

    if (!readInSegments)
    {
        segmentSize = ALIGN_NEXT(instructions->compressedSize, 32);
        gDataDecompressorValues.segmentCount = -1;
    }
    else
    {
        segmentSize = 0x20000;
        gDataDecompressorValues.segmentCount = 0;
    }

    // Set the top of the and bottom of the write to the same output
    gDataDecompressorValues.DataWriteBottom = pOutData;
    gDataDecompressorValues.DataWriteTop =  pOutData;
    gDataDecompressorValues.DataReadBottom = gDataDecompressorValues.CachedDataReadBottom = pCompressedData;

    gDataDecompressorValues.DataReadTop = (u8 *)pCompressedData + segmentSize;
    gDataDecompressorValues.error = 0;
    gDataDecompressorValues.ReadOffset = 0;
    gDataDecompressorValues.BitsInBuffer = 0;
    gDataDecompressorValues.bitBuffer = 0;
    gDataDecompressorValues.compressedFlag = instructions->compressionFlag;
    gDataDecompressorValues.ShouldWriteDataFlag = TRUE;
    OSResumeThread(&gDataDecompressorValues.t);
    return;
}

/*================================================================================*/

extern u8 myStack[2][0x1000];

void StartThreadForReadingFromDisk()
{
    OSCreateThread(&gDataDecompressorValues.t, ReadDataFromDisk, NULL, myStack[1], sizeof(myStack[1]), 0x1f, 1);
    OSResumeThread(&gDataDecompressorValues.t);
}

/*================================================================================*/

void *ReadDataFromDisk(void *)
{
    OSInitSemaphore(gDataDecompressorValues.s, 3);
    while (1)
    {
        gDataDecompressorValues.ShouldWriteDataFlag = FALSE;
        OSSuspendThread(&gDataDecompressorValues.t);

        switch (gDataDecompressorValues.compressedFlag - 1)
        {
        case 0:
            DecompressDiskData();
            break;
        }
    }
}

/*================================================================================*/

// NONMATCHING 81%: the original copy loop is a bare mtctr/bdnz with no zero-length guard and
// it saves r27-r31 (stmw) while using only r27/r31. `for` unrolls 8x; with
// `#pragma ppc_unroll_factor_limit 1` a `cmplwi n,0; ble` guard remains; do-while gives subic./bne.
#if NONMATCHING
void DecompressDiskData(void)
{
    DataVars *v = &gDataDecompressorValues;
    u32 lookBack;
    u32 repetition;
    u8 *tP;

    while (TRUE)
    {
        // a 1 flag bit means a literal byte follows
        if (ReadBits(LZSS_FLAG_SIZE))
        {
            *v->DataWriteTop++ = ReadBits(LZSS_BYTE_SIZE);
            v->BytesToRead--;
        }
        // otherwise copy `repetition` bytes from `lookBack` bytes back in the output
        else
        {
            // a lookback of 0 means the last byte written, DataWriteTop[-1]
            lookBack = ReadBits(v->LookBackSize) + 1;
            repetition = ReadBits(v->RepetitionSize) + LZSS_MINIMUM_REPETITION_SIZE;

            v->BytesToRead -= repetition;

            // reading before the start of the output, or past the expected size, is an error
            if ((v->BytesToRead < 0) | (v->DataWriteTop - lookBack < v->DataWriteBottom))
                break;

            // repetition is at least 2
            tP = v->DataWriteTop;
            do
            {
                *tP = *(tP - lookBack);
                tP++;
            } while (--repetition != 0);

            v->DataWriteTop = tP;
        }

        // done once every expected byte has been written
        if (!v->BytesToRead)
            return;
    }

    v->error = 1;
}
#endif

/*================================================================================*/

u32 ReadBits(u32 bits)
{
    u32 bitsNeededToRead;
    int interrupts;
    u8 bitsForNextBuffer;
    u32 toReturn;

    if (gDataDecompressorValues.BitsInBuffer >= bits)
    {
        // we have enough bits in the buffer, just cycle them out
        gDataDecompressorValues.BitsInBuffer -= bits;
        // push out the top bits, and then move back to just hold the bottom bits, worse than a mask? maybe faster for cpu
        toReturn = gDataDecompressorValues.bitBuffer << (32 - bits) >> (32 - bits);
        gDataDecompressorValues.bitBuffer >>= bits;
    }
    else
    {
        // not enough bits, figure out how many we need
        bitsNeededToRead = bits - gDataDecompressorValues.BitsInBuffer;
        // the bits left in our buffer will be the top bits of our value
        toReturn = gDataDecompressorValues.bitBuffer << bitsNeededToRead;

        // make sure we have valid data?
        while (!gDataDecompressorValues.ReadOffset && !gDataDecompressorValues.segmentCount)
        {
            // nop
        }

        // read a new u32 into our buffer
        gDataDecompressorValues.bitBuffer = *(u32 *)&gDataDecompressorValues.DataReadBottom[gDataDecompressorValues.ReadOffset];
        // how many bits our next buffer will hold after we remove the rest of the current data
        bitsForNextBuffer = 32 - bitsNeededToRead;
        // push out most of the new bits, and be left with bottom bits of the buffer
        // `or` it into the result
        toReturn |= (gDataDecompressorValues.bitBuffer << bitsForNextBuffer) >> bitsForNextBuffer;

        // update the bit variables
        gDataDecompressorValues.BitsInBuffer = bitsForNextBuffer;
        // cycle out the used bits
        gDataDecompressorValues.bitBuffer >>= bitsNeededToRead;
        // update the read offset
        gDataDecompressorValues.ReadOffset += sizeof(u32);

        // if we've read a full 32Kb
        if (gDataDecompressorValues.ReadOffset == 0x8000)
        {
            // update the read offset by moving the bottom pointer
            gDataDecompressorValues.ReadOffset = 0;
            gDataDecompressorValues.DataReadBottom += 0x8000;
            // If we've read too far, reset the pointer to the bottom of the array
            if (gDataDecompressorValues.DataReadBottom == gDataDecompressorValues.DataReadTop)
            {
                gDataDecompressorValues.DataReadBottom = gDataDecompressorValues.CachedDataReadBottom;
            }
            // signal a thread to update the cache of data to read
            interrupts = OSDisableInterrupts();
            gDataDecompressorValues.segmentCount--;
            OSSignalSemaphore(&gDataDecompressorValues.s);
            OSRestoreInterrupts(interrupts);
        }
    }
    return toReturn;
}

/*================================================================================*/
