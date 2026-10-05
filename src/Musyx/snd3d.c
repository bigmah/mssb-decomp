#include "musyx/musyx.h"
#include "musyx/musyx_priv.h"
#include "musyx/synth.h"
#include "stl/math.h"

static u8 s3dCallCnt;
static SND_EMITTER *s3dEmitterRoot;
static SND_LISTENER *s3dListenerRoot;
static SND_ROOM *s3dRoomRoot;
static u8 snd_base_studio;
static u8 snd_max_studios;
static u8 s3dUseMaxVoices;
static u8 s3dFlag4;
static void (*s3dCallback)(SND_EMITTER *em, SND_FVECTOR *lpos, SND_FVECTOR *lhead, SND_FVECTOR *lup,
                           SND_FVECTOR *epos, SND_FVECTOR *edir, f32 *out1, f32 *out2);

static void CalcEmitter(SND_EMITTER *em, f32 *vol, f32 *doppler, f32 *xPan, f32 *yPan, f32 *zPan,
                        f32 *filter)
{
    SND_LISTENER *li;  // r31
    SND_FVECTOR d;
    SND_FVECTOR v;
    SND_FVECTOR p;
    f32 relspeed;
    f32 distance;
    f32 new_distance;
    f32 ft;
    f32 vd;
    f32 cvol;
    f32 fl2;
    f32 fl;
    f32 flMax;
    f32 flMin;
    SND_FVECTOR pan;
    u32 n;
    f32 *fp;

    *vol = 0.f;
    *doppler = 1.f;
    pan.z = 0.f;
    flMin = 1.f;
    flMax = 1.f;
    pan.y = 0.f;
    pan.x = 0.f;

    for (n = 0, li = s3dListenerRoot; li != NULL; li = li->next, ++n)
    {
        d.x = em->pos.x - (li->pos.x + li->heading.x * li->volPosOff);
        d.y = em->pos.y - (li->pos.y + li->heading.y * li->volPosOff);
        d.z = em->pos.z - (li->pos.z + li->heading.z * li->volPosOff);

        distance = dolsqrtf(d.x * d.x + d.y * d.y + d.z * d.z);

        if (em->maxDis >= distance)
        {
            vd = distance / em->maxDis;

            if (em->volPush >= 0.f)
            {
                cvol = li->vol * (em->minVol + (em->maxVol - em->minVol) *
                                                   (1.f - ((1.f - em->volPush) * vd +
                                                           em->volPush * vd * vd)));
            }
            else
            {
                cvol = li->vol * (em->minVol + (em->maxVol - em->minVol) *
                                                   (1.f - ((em->volPush + 1.f) * vd -
                                                           em->volPush * (1.f - (1.f - vd) * (1.f - vd)))));
            }

            if ((em->flags & 0x180) && s3dCallback != NULL)
            {
                s3dCallback(em, &li->pos, &li->heading, &li->up, &em->pos, &em->dir, &fl, &fl2);
                cvol *= 1.f - fl;
            }
            else
            {
                fl2 = 0.f;
            }

            if (s3dFlag4)
            {
                *vol += cvol;
            }
            else if (*vol < cvol)
            {
                *vol = cvol;
            }

            if (!(em->flags & 0x80000))
            {
                if ((em->flags & 0x8) || (li->flags & 1))
                {
                    v.x = li->dir.x - em->dir.x;
                    v.y = li->dir.y - em->dir.y;
                    v.z = li->dir.z - em->dir.z;
                    relspeed = dolsqrtf(v.x * v.x + v.y * v.y + v.z * v.z);

                    if (relspeed > 0.f)
                    {
                        ft = 1.f / 60.f;
                        d.x = (em->pos.x + em->dir.x * ft) - (li->pos.x + li->dir.x * ft);
                        d.y = (em->pos.y + em->dir.y * ft) - (li->pos.y + li->dir.y * ft);
                        d.z = (em->pos.z + em->dir.z * ft) - (li->pos.z + li->dir.z * ft);

                        new_distance = dolsqrtf(d.x * d.x + d.y * d.y + d.z * d.z);

                        if (new_distance < distance)
                        {
                            ft = li->soundSpeed - relspeed;
                            if (ft >= 0.00001f)
                            {
                                *doppler = li->soundSpeed / ft;
                            }
                            else
                            {
                                *doppler = 100000.f * li->soundSpeed;
                            }
                        }
                        else
                        {
                            *doppler = li->soundSpeed / (li->soundSpeed + relspeed);
                        }
                    }
                }

                if (distance != 0.f)
                {
                    salApplyMatrix(&li->mat, &em->pos, &p);

                    if (p.z <= 0.f)
                    {
                        pan.z += -li->surroundDisFront < p.z ? -p.z / li->surroundDisFront : 1.f;
                    }
                    else
                    {
                        pan.z += li->surroundDisBack > p.z ? -p.z / li->surroundDisBack : -1.f;
                    }

                    if (p.x != 0.f || p.y != 0.f || p.z != 0.f)
                    {
                        salNormalizeVector(&p);
                    }

                    pan.x += p.x;
                    pan.y -= p.y;
                    if (em->flags & 0x80)
                    {
                        if (flMin > 0.f)
                        {
                            flMin = 0.f;
                        }
                    }

                    if (flMax > fl2)
                    {
                        flMax = fl2;
                    }
                }
                else
                {
                    *filter = 0.f;
                }
            }
        }
    }

    if (n != 0)
    {
        *xPan = pan.x / n;
        *yPan = pan.y / n;
        *zPan = pan.z / n;
    }

    if (em->flags & 0x80)
    {
        if (em->flags & 0x100)
        {
            *filter = flMin < flMax ? flMax : flMin;
        }
        else
        {
            *filter = flMin;
        }
    }
    else if (em->flags & 0x100)
    {
        *filter = flMax;
    }
    else
    {
        *filter = 0.f;
    }
}

static u8 clip127(u8 v)
{
    if (v <= 0x7f)
    {
        return v;
    }
    return 0x7f;
}

static u16 clip3FFF(f32 v)
{
    if (v > 16383.f)
    {
        return 0x3fff;
    }
    return v;
}

static void SetFXParameters(SND_EMITTER *const em, f32 vol, f32 xPan, f32 yPan, f32 zPan, f32 doppler,
                            f32 filter)
{
    SND_VOICEID vid;
    u8 i;
    SND_PARAMETER *pPtr;

    vid = em->vid;
    if ((em->flags & 0x100000) != 0)
    {
        synthFXSetCtrl(vid, 7, clip127((em->fade * vol) * 127.f));
    }
    else
    {
        synthFXSetCtrl(vid, 7, clip127(vol * 127.f));
    }

    synthFXSetCtrl(vid, 10, clip127((1.f + xPan) * 64.f));
    synthFXSetCtrl(vid, 131, clip127((1.f - zPan) * 64.f));
    synthFXSetCtrl14(vid, 132, clip3FFF(doppler * 8192.f));

    if (em->flags & 0x180)
    {
        if (filter != 0.f)
        {
            synthFXSetCtrl14(vid, 31, clip3FFF(16383.f * filter));
            synthFXSetCtrl(vid, 79, 127);
        }
        else
        {
            synthFXSetCtrl(vid, 79, 0);
        }
    }

    if (em->paraInfo != NULL)
    {
        pPtr = em->paraInfo->paraArray;
        for (i = 0; i < em->paraInfo->numPara; ++pPtr, ++i)
        {
            if ((pPtr->ctrl & 0xFF00) == 0)
            {
                if (pPtr->ctrl < 0x40 || pPtr->ctrl == 0x80 || pPtr->ctrl == 0x84)
                {
                    synthFXSetCtrl14(vid, pPtr->ctrl, (pPtr->paraData).value14);
                }
                else
                {
                    synthFXSetCtrl(vid, pPtr->ctrl, (pPtr->paraData).value7);
                }
            }
        }
    }
}

static void EmitterShutdown(SND_EMITTER *em)
{
    if (em->next != NULL)
    {
        em->next->prev = em->prev;
    }

    if (em->prev != NULL)
    {
        em->prev->next = em->next;
    }
    else
    {
        s3dEmitterRoot = em->next;
    }

    em->flags &= 0xFFFF;
    if (em->vid != -1)
    {
        synthSendKeyOff(em->vid);
    }
}

bool32 sndUpdateEmitter(SND_EMITTER *em, SND_FVECTOR *pos, SND_FVECTOR *dir, u8 maxVol)
{
    if (sndActive)
    {
        hwDisableIrq();

        em->pos = *pos;
        em->dir = *dir;
        em->maxVol = maxVol / 127.f;
        if (em->minVol > em->maxVol)
        {
            em->minVol = em->maxVol;
        }

        hwEnableIrq();
        return TRUE;
    }

    return FALSE;
}

bool32 sndCheckEmitter(SND_EMITTER *em)
{
    if (sndActive)
    {
        return (em->flags & 0x10000) != 0;
    }
    return FALSE;
}

static u8 GetEmitterKey(SND_EMITTER *em)
{
    u8 i;
    SND_PARAMETER *pPtr;
    u8 key;

    if (em->paraInfo == NULL)
    {
        key = 0xFF;
    }
    else
    {
        pPtr = em->paraInfo->paraArray;
        for (i = 0; i < em->paraInfo->numPara; ++pPtr, ++i)
        {
            if (pPtr->ctrl == 0x8000)
            {
                return pPtr->paraData.value7;
            }
        }
        key = 0xFF;
    }
    return key;
}

static SND_VOICEID AddEmitter(SND_EMITTER *em_buffer, SND_FVECTOR *pos, SND_FVECTOR *dir,
                              f32 maxDis, f32 comp, u32 flags, u16 fxid, u32 groupid, u8 maxVol,
                              u8 minVol, SND_ROOM *room, SND_PARAMETER_INFO *para, u8 studio)
{
    static SND_EMITTER tmp_em;
    SND_EMITTER *em;
    f32 xPan;
    f32 yPan;
    f32 zPan;
    f32 cvol;
    f32 pitch;
    f32 filter;
    u8 key;
    u8 i;
    SND_PARAMETER *pPtr;

    hwDisableIrq();
    em = em_buffer == NULL ? &tmp_em : em_buffer;

    em->flags = flags;
    em->pos = *pos;
    em->dir = *dir;
    em->maxDis = maxDis;
    em->fxid = fxid;
    em->maxVol = maxVol * (1.f / 127.f);
    em->minVol = minVol * (1.f / 127.f);
    em->volPush = comp;
    em->group = groupid;
    em->studio = studio;

    if (em_buffer == NULL)
    {
        CalcEmitter(em, &cvol, &pitch, &xPan, &yPan, &zPan, &filter);
        if (cvol == 0.f)
        {
            hwEnableIrq();
            return -1;
        }

        key = GetEmitterKey(em);

        em->vid = synthFXStart(em->fxid, key, 127, 64, em->studio, (em->flags & 0x10) != 0);
        if (em->vid == -1)
        {
            hwEnableIrq();
            return -1;
        }

        SetFXParameters(em, cvol, xPan, yPan, zPan, pitch, filter);

        hwEnableIrq();
        return em->vid;
    }
    else
    {
        if ((em->next = s3dEmitterRoot) != NULL)
        {
            s3dEmitterRoot->prev = em;
        }

        em->prev = NULL;
        s3dEmitterRoot = em;
        em->paraInfo = para;
        em->vid = -1;
        em->VolLevelCnt = 0;
        em->flags |= 0x30000;
        em->maxVoices = synthFXGetMaxVoices(em->fxid);
    }

    hwEnableIrq();
    return -1;
}

unsigned long sndAddEmitter(SND_EMITTER *em_buffer, SND_FVECTOR *pos, SND_FVECTOR *dir, f32 maxDis,
                            f32 comp, unsigned long flags, unsigned short fxid,
                            unsigned char maxVol, unsigned char minVol, SND_ROOM *room)
{
    if (sndActive)
    {
        return AddEmitter(em_buffer, pos, dir, maxDis, comp, flags, fxid, fxid | 0x80000000, maxVol,
                          minVol, room, NULL, 0);
    }

    return -1;
}

unsigned long sndRemoveEmitter(SND_EMITTER *em)
{
    if (sndActive)
    {
        hwDisableIrq();
        if (em->flags & 0x10000)
        {
            EmitterShutdown(em);
        }

        hwEnableIrq();
        return TRUE;
    }

    return FALSE;
}

SND_VOICEID sndEmitterVoiceID(SND_EMITTER *em)
{
    unsigned long ret; // r31

    ret = 0xffffffff;
    if (sndActive != FALSE)
    {
        hwDisableIrq();
        if ((em->flags & 0x10000) != 0)
        {
            ret = em->vid;
        }
        hwEnableIrq();
    }
    return ret;
}

void s3dKillAllEmitter()
{
    struct SND_EMITTER *em;  // r31
    struct SND_EMITTER *nem; // r30

    em = s3dEmitterRoot;
    while (em != NULL)
    {
        nem = em->next;
        sndRemoveEmitter(em);
        em = nem;
    }
}

void s3dKillEmitterByFXID(FX_TAB *fxTab, unsigned long num)
{
    struct SND_EMITTER *em;  // r31
    struct SND_EMITTER *nem; // r29
    unsigned long j;         // r30

    for (em = s3dEmitterRoot; em != NULL; em = nem)
    {
        nem = em->next;
        for (j = 0; j < num; ++j)
        {
            if (em->fxid == fxTab[j].id)
            {
                sndRemoveEmitter(em);
                break;
            }
        }
    }
}

static void MakeListenerMatrix(SND_LISTENER *li)
{
    struct SND_FMATRIX mat; // r1+0xC
    salCrossProduct(&li->right, &li->heading, &li->up);
    mat.m[0][0] = li->right.x;
    mat.m[1][0] = li->right.y;
    mat.m[2][0] = li->right.z;
    mat.m[0][1] = li->up.x;
    mat.m[1][1] = li->up.y;
    mat.m[2][1] = li->up.z;
    mat.m[0][2] = -li->heading.x;
    mat.m[1][2] = -li->heading.y;
    mat.m[2][2] = -li->heading.z;
    mat.t[0] = li->pos.x;
    mat.t[1] = li->pos.y;
    mat.t[2] = li->pos.z;
    salInvertMatrix(&li->mat, &mat);
}

unsigned long sndUpdateListener(SND_LISTENER *li, SND_FVECTOR *pos, SND_FVECTOR *dir,
                                SND_FVECTOR *heading, SND_FVECTOR *up, u8 vol)
{
    if (sndActive)
    {
        hwDisableIrq();
        li->pos = *pos;
        li->dir = *dir;
        li->heading = *heading;
        li->up = *up;

        MakeListenerMatrix(li);
        li->vol = vol / 127.f;

        hwEnableIrq();
        return TRUE;
    }

    return FALSE;
}

unsigned long sndAddListener(SND_LISTENER *li, SND_FVECTOR *pos, SND_FVECTOR *dir,
                             SND_FVECTOR *heading, SND_FVECTOR *up, f32 front_sur, f32 back_sur,
                             f32 soundSpeed, unsigned long flags, unsigned char vol, f32 *unk)
{
    if (sndActive)
    {
        hwDisableIrq();
        if ((li->next = s3dListenerRoot) != NULL)
        {
            s3dListenerRoot->prev = li;
        }

        li->prev = NULL;
        s3dListenerRoot = li;
        li->pos = *pos;
        li->dir = *dir;
        li->heading = *heading;
        li->up = *up;
        li->surroundDisFront = front_sur;
        li->surroundDisBack = back_sur;
        li->soundSpeed = soundSpeed;
        li->volPosOff = 0.f;
        MakeListenerMatrix(li);
        li->flags = flags;
        li->vol = vol / 127.f;
        if (unk != NULL)
        {
            li->unk8C = *unk;
        }
        else
        {
            li->unk8C = 1.f;
        }
        hwEnableIrq();
        return TRUE;
    }

    return FALSE;
}

unsigned long sndRemoveListener(SND_LISTENER *li)
{
    if (sndActive)
    {
        hwDisableIrq();

        if (li->next != NULL)
        {
            li->next->prev = li->prev;
        }

        if (li->prev != NULL)
        {
            li->prev->next = li->next;
        }
        else
        {
            s3dListenerRoot = li->next;
        }
        hwEnableIrq();
        return TRUE;
    }

    return FALSE;
}

typedef struct START_LIST
{
    // total size: 0x20
    struct START_LIST *next; // offset 0x0, size 0x4
    f32 vol;                 // offset 0x4, size 0x4
    f32 xPan;                // offset 0x8, size 0x4
    f32 yPan;                // offset 0xC, size 0x4
    f32 zPan;                // offset 0x10, size 0x4
    f32 pitch;               // offset 0x14, size 0x4
    f32 unk18;               // offset 0x18, size 0x4
    SND_EMITTER *em;         // offset 0x1C, size 0x4
} START_LIST;

typedef struct RUN_LIST
{
    // total size: 0xC
    struct RUN_LIST *next; // offset 0x0, size 0x4
    f32 vol;               // offset 0x4, size 0x4
    SND_EMITTER *em;       // offset 0x8, size 0x4
} RUN_LIST;

typedef struct START_GROUP
{
    // total size: 0x10
    unsigned long id;          // offset 0x0, size 0x4
    struct START_LIST *list;   // offset 0x4, size 0x4
    struct RUN_LIST *running;  // offset 0x8, size 0x4
    unsigned short numRunning; // offset 0xC, size 0x2
} START_GROUP;

static START_GROUP startGroup[64];  // size: 0x400
static u8 startGroupNum;            // size: 0x1
static START_LIST startListNum[64]; // size: 0x800
static u8 startListNumnum;          // size: 0x1
static RUN_LIST runList[64];        // size: 0x300
static u8 runListNum;               // size: 0x1

void ClearStartList()
{
    startGroupNum = 0;
    startListNumnum = 0;
    runListNum = 0;
}

void AddRunningEmitter(SND_EMITTER *em, f32 vol)
{
    long i;        // r30
    RUN_LIST *rl;  // r29
    RUN_LIST *lrl; // r28

    for (i = 0; i < startGroupNum; ++i)
    {
        if (em->group == startGroup[i].id)
        {
            break;
        }
    }

    if (i == startGroupNum)
    {
        startGroup[i].list = NULL;
        startGroup[i].running = NULL;
        startGroup[i].numRunning = 0;
        startGroup[i].id = em->group;
        ++startGroupNum;
    }

    ++startGroup[i].numRunning;

    lrl = NULL;
    for (rl = startGroup[i].running; rl != NULL; rl = rl->next)
    {
        if (rl->vol > vol)
        {
            break;
        }
        lrl = rl;
    }

    if (lrl == NULL)
    {
        startGroup[i].running = &runList[runListNum];
    }
    else
    {
        lrl->next = &runList[runListNum];
    }

    runList[runListNum].next = rl;
    runList[runListNum].em = em;
    runList[runListNum++].vol = vol;
}

bool32 AddStartingEmitter(SND_EMITTER *em, f32 vol, f32 xPan, f32 yPan, f32 zPan, f32 pitch, f32 unk18)
{
    long i;         // r30
    START_LIST *sl; // r29

    for (i = 0; i < startGroupNum; ++i)
    {
        if (em->group == startGroup[i].id)
        {
            break;
        }
    }

    if (i == startGroupNum)
    {
        if (startGroupNum == 64)
        {
            return FALSE;
        }

        startGroup[i].list = NULL;
        startGroup[i].running = NULL;
        startGroup[i].numRunning = 0;
        startGroup[i].id = em->group;
        ++startGroupNum;
    }

    if (startListNumnum == 64)
    {
        return FALSE;
    }

    sl = startGroup[i].list;

    if (sl != NULL)
    {
        for (; sl->next != NULL; sl = sl->next)
        {
            if (sl->vol < vol)
            {
                break;
            }
        }
        startListNum[startListNumnum].next = sl->next;
        sl->next = &startListNum[startListNumnum];
    }
    else
    {
        startListNum[startListNumnum].next = startGroup[i].list;
        startGroup[i].list = &startListNum[startListNumnum];
    }

    startListNum[startListNumnum].em = em;
    startListNum[startListNumnum].pitch = pitch;
    startListNum[startListNumnum].unk18 = unk18;
    startListNum[startListNumnum].xPan = xPan;
    startListNum[startListNumnum].yPan = yPan;
    startListNum[startListNumnum].zPan = zPan;
    startListNum[startListNumnum++].vol = vol;

    return TRUE;
}

void StartContinousEmitters()
{
    long i;          // r30
    START_LIST *sl;  // r29
    SND_EMITTER *em; // r31
    f32 dv;          // r63

    for (i = 0; i < startGroupNum; ++i)
    {

        for (sl = startGroup[i].list; sl != NULL; sl = sl->next)
        {
            if ((startGroup[i].running != NULL) &&
                !(((s3dUseMaxVoices != '\0' && ((startGroup[i].id & 0x80000000) != 0)) &&
                   (startGroup[i].numRunning < startGroup[i].list->em->maxVoices))))
            {

                dv = sl->vol - (startGroup[i].running)->vol;
                if (dv <= 0.08f)
                {
                    continue;
                }
                else if (dv <= 0.15f)
                {
                    if (++sl->em->VolLevelCnt < 20)
                    {
                        continue;
                    }
                }
                else
                {
                    sl->em->VolLevelCnt = 0;
                }
            }
            em = sl->em;

            if ((em->vid =
                     synthFXStart(em->fxid, GetEmitterKey(em), 127, 64, em->studio,
                                  (em->flags & 0x10) != 0)) == -1)
            {
            set_flags:
                if (!(em->flags & 0x2))
                {
                    em->flags |= 0x40000;
                    em->flags &= ~0x20000;
                }
            }
            else
            {
                if (!(em->flags & 0x20))
                {
                    em->flags |= 0x100000;
                    em->fade = 0.f;
                }
                else
                {
                    em->fade = 1.f;
                }
                SetFXParameters(em, sl->vol, sl->xPan, sl->yPan, sl->zPan, sl->pitch, sl->unk18);
                em->flags &= ~0x20000;
                ++startGroup[i].numRunning;
                if (startGroup[i].running != NULL)
                {
                    startGroup[i].running = startGroup[i].running->next;
                }
            }
        }
    }
}

void s3dHandle()
{
    SND_EMITTER *em;  // r31
    SND_EMITTER *nem; // r30
    f32 vol;          // r1+0x18
    f32 xPan;         // r1+0x14
    f32 yPan;         // r1+0x10
    f32 zPan;         // r1+0xC
    f32 pitch;        // r1+0x8
    f32 filter;

    if (s3dCallCnt != 0)
    {
        --s3dCallCnt;
        return;
    }
    s3dCallCnt = 3;
    ClearStartList();
    em = s3dEmitterRoot;
    for (; em != NULL; em = nem)
    {
        nem = em->next;
        if ((em->flags & 0x40000) != 0)
        {
            EmitterShutdown(em);
            continue;
        }
        if ((em->flags & 0x20001) != 0)
        {
            CalcEmitter(em, &vol, &pitch, &xPan, &yPan, &zPan, &filter);
        }

        if (!(em->flags & 0x80000))
        {
            if (em->flags & 0x20000)
            {
                if (vol == 0.f && em->flags & 0x4)
                {
                    em->flags |= 0x80000;
                    em->flags &= ~0x20000;
                    goto found_emitter;
                }
                else if (vol == 0.f && em->flags & 0x40)
                {
                    EmitterShutdown(em);
                    continue;
                }

                if (em->flags & 1)
                {
                    if (AddStartingEmitter(em, vol, xPan, yPan, zPan, pitch, filter))
                    {
                        continue;
                    }
                }
                else
                {
                    if ((em->vid =
                             synthFXStart(em->fxid, GetEmitterKey(em), 127, 64, em->studio,
                                          (em->flags & 0x10) != 0)) == -1)
                    {

                    derp:
                        if (!(em->flags & 2))
                        {
                            em->flags |= 0x40000;
                            em->flags &= ~0x20000;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
            else if ((em->vid = sndFXCheck(em->vid)) == -1)
            {
                if ((em->flags & 2))
                {
                    em->flags |= 0x20000;
                }
                else
                {
                    em->flags |= 0x40000;
                }
            }

        found_emitter:
            if (em->vid != -1)
            {
                if ((em->flags & 1) != 0)
                {
                    AddRunningEmitter(em, vol);
                }
                if ((vol == 0.f) && ((em->flags & 4) != 0))
                {
                    synthSendKeyOff(em->vid);
                    em->vid = 0xffffffff;
                    if ((em->flags & 2))
                    {
                        em->flags |= 0x80000;
                    }
                    else
                    {
                        em->flags |= 0x40000;
                    }
                }
                else
                {
                    SetFXParameters(em, vol, xPan, yPan, zPan, pitch, filter);
                }
            }
            if ((em->flags & 0x100000) != 0)
            {
                em->fade += .3f;
                if (em->fade >= 1.f)
                {
                    em->flags &= ~0x100000;
                }
            }
        }
        else if (vol != 0.f)
        {
            em->flags &= ~0x80000;
            em->flags |= 0x20000;
        }
    }
    StartContinousEmitters();
}

void s3dInit(u32 flags)
{
    s3dEmitterRoot = 0;
    s3dListenerRoot = 0;
    s3dRoomRoot = 0;
    snd_base_studio = 1;
    snd_max_studios = 3;
    s3dCallCnt = 0;
    s3dUseMaxVoices = ((flags & 2) != 0);
    s3dFlag4 = ((flags & 4) != 0);
}

void s3dExit() {}
