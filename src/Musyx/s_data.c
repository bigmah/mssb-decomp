
#include "musyx/musyx_priv.h"
#include "musyx/synth.h"

typedef struct DATA_STACK {
  struct DATA_STACK* prev; // offset 0x0
  s32 unk4;                // offset 0x4
  s16 sp;                  // offset 0x8
  GSTACK gs[128];          // offset 0xC
  u32 aramBase;            // offset 0x60C
  u32 aramEnd;             // offset 0x610
  u32 aramCur;             // offset 0x614
} DATA_STACK;

static DATA_STACK dataStack0;
static s32 dataStackNum;
static DATA_STACK* dataStackCur;
static DATA_STACK* dataStackRoot;

void dataInitStack(u32 aramBase, u32 aramSize) {
  dataStackRoot = NULL;
  dataStack0.unk4 = -2;
  dataStack0.sp = 0;
  dataStack0.aramBase = aramBase;
  dataStack0.aramCur = aramBase;
  dataStack0.aramEnd = aramBase + aramSize;
  dataStack0.prev = NULL;
  dataStackRoot = &dataStack0;
  dataStackNum = 0;
  dataStackCur = &dataStack0;
}

static MEM_DATA* GetPoolAddr(u16 id, MEM_DATA* m) {
  while (m->nextOff != 0xFFFFFFFF) {
    if (m->id == id) {
      return m;
    }

    m = (MEM_DATA*)((u8*)m + m->nextOff);
  }
  return NULL;
}

static MEM_DATA* GetMacroAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->macroOff));
}

static MEM_DATA* GetCurveAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->curveOff));
}
static MEM_DATA* GetKeymapAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->keymapOff));
}
static MEM_DATA* GetLayerAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->layerOff));
}

static void InsertData(u16 id, void* data, u8 dataType, u32 remove) {
  MEM_DATA* m; // r30

  switch (dataType) {
  case 0:
    if (!remove) {
      if ((m = GetMacroAddr(id, data)) != NULL) {
        dataInsertMacro(id, &m->data.cmd);

      } else {
        dataInsertMacro(id, NULL);
      }
    } else {
      dataRemoveMacro(id);
    }
    break;
  case 2: {
    id |= 0x4000;
    if (!remove) {
      if ((m = GetKeymapAddr(id, data)) != NULL) {
        dataInsertKeymap(id, &m->data.map);
      } else {
        dataInsertKeymap(id, NULL);
      }
    } else {
      dataRemoveKeymap(id);
    }
  } break;
  case 3: {
    id |= 0x8000;
    if (!remove) {
      if ((m = GetLayerAddr(id, data)) != NULL) {
        dataInsertLayer(id, &m->data.layer.entry, m->data.layer.num);
      } else {
        dataInsertLayer(id, NULL, 0);
      }
    } else {
      dataRemoveLayer(id);
    }
  } break;
  case 4:
    if (!remove) {
      if ((m = GetCurveAddr(id, data)) != NULL) {
        dataInsertCurve(id, &m->data.tab);
      } else {
        dataInsertCurve(id, NULL);
      }
    } else {
      dataRemoveCurve(id);
    }
    break;
  case 1:
    if (!remove) {
      dataAddSampleReference(id, &dataStackCur->aramBase);
    } else {
      dataRemoveSampleReference(id, &dataStackCur->aramBase);
    }
    break;
  }
}

static void ScanIDList(u16* ref, void* data, u8 dataType, u32 remove) {
  u16 id; // r30

  while (*ref != 0xFFFF) {
    if ((*ref & 0x8000)) {
      id = *ref & 0x3fff;
      while (id <= ref[1]) {
        InsertData(id, data, dataType, remove);
        ++id;
      }
      ref += 2;

    } else {
      InsertData(*ref++, data, dataType, remove);
    }
  }
}

static void ScanIDListReverse(u16* refBase, void* data, u8 dataType, u32 remove) {
  s16 id;
  u16* ref;

  if (*refBase != 0xffff) {
    ref = refBase;
    while (*ref != 0xffff) {
      ref++;
    }
    ref--;

    while (ref >= refBase) {
      if (ref != refBase) {
        if ((ref[-1] & 0x8000) != 0) {
          id = *ref;
          while (id >= (s16)(ref[-1] & 0x3fff)) {
            InsertData(id, data, dataType, remove);
            id--;
          }
          ref -= 2;
        } else {
          InsertData(*ref, data, dataType, remove);
          ref--;
        }
      } else {
        InsertData(*ref, data, dataType, remove);
        ref--;
      }
    }
  }
}

static void InsertMacros(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 0, 0); }

static void InsertCurves(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 4, 0); }

static void InsertKeymaps(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 2, 0); }

static void InsertLayers(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 3, 0); }

static void RemoveMacros(unsigned short* ref) { ScanIDList(ref, NULL, 0, 1); }

static void RemoveCurves(unsigned short* ref) { ScanIDList(ref, NULL, 4, 1); }

static void RemoveKeymaps(unsigned short* ref) { ScanIDList(ref, NULL, 2, 1); }

static void RemoveLayers(unsigned short* ref) { ScanIDList(ref, NULL, 3, 1); }

static void InsertSamples(u16* ref, void* samples, void* sdir) {
  samples = hwTransAddr(samples);
  if (dataInsertSDir((SDIR_DATA*)sdir, samples)) {
    ScanIDList(ref, sdir, 1, 0);
  }
}

static void RemoveSamples(unsigned short* ref, void* sdir) {
  ScanIDListReverse(ref, NULL, 1, 1);
  dataRemoveSDir(sdir);
}

static void InsertFXTab(unsigned short gid, FX_DATA* fd) { dataInsertFX(gid, fd->fx, fd->num); }

static void RemoveFXTab(unsigned short gid) { dataRemoveFX(gid); }

void sndSetSampleDataUploadCallback(void* (*callback)(unsigned long, unsigned long),
                                    unsigned long chunckSize) {
  hwSetSaveSampleCallback(callback, chunckSize);
}

u32 sndPushGroup(void* prj_data, u16 gid, void* samples, void* sdir, void* pool) {
  GROUP_DATA* g; // r31

  if (sndActive && dataStackCur->sp < 128) {
    g = prj_data;

    while (g->nextOff != 0xFFFFFFFF) {
      if (g->id == gid) {
        dataStackCur->gs[dataStackCur->sp].gAddr = g;
        dataStackCur->gs[dataStackCur->sp].prjAddr = prj_data;
        dataStackCur->gs[dataStackCur->sp].sdirAddr = sdir;
        InsertSamples((u16*)((u8*)prj_data + g->sampleOff), samples, sdir);
        InsertMacros((u16*)((u8*)prj_data + g->macroOff), pool);
        InsertCurves((u16*)((u8*)prj_data + g->curveOff), pool);
        InsertKeymaps((u16*)((u8*)prj_data + g->keymapOff), pool);
        InsertLayers((u16*)((u8*)prj_data + g->layerOff), pool);
        if (g->type == 1) {
          InsertFXTab(gid, (FX_DATA*)((u8*)prj_data + g->data.song.normpageOff));
        }
        hwSyncSampleMem();
        ++dataStackCur->sp;
        return 1;
      }

      g = (GROUP_DATA*)((u8*)prj_data + g->nextOff);
    }
  }

  MUSY_DEBUG("Group ID=%d could not be pushed.\n", gid);
  return 0;
}

/*










*/
unsigned long sndPopGroup() {
  struct GROUP_DATA* g;
  struct SDIR_DATA* sdir;
  void* prj;
  struct FX_DATA* fd;

  g = dataStackCur->gs[--dataStackCur->sp].gAddr;
  prj = dataStackCur->gs[dataStackCur->sp].prjAddr;
  sdir = dataStackCur->gs[dataStackCur->sp].sdirAddr;
  hwDisableIrq();

  if (g->type == 1) {
    fd = (FX_DATA*)((u8*)prj + g->data.song.normpageOff);
    s3dKillEmitterByFXID(fd->fx, fd->num);
  } else {
    seqKillInstancesByGroupID(g->id);
  }

  synthKillVoicesByMacroReferences((u16*)((u8*)prj + g->macroOff));
  synthKillVoicesBySampleReferences((u16*)((u8*)prj + g->sampleOff));
  hwEnableIrq();
  RemoveSamples((u16*)((u8*)prj + g->sampleOff), sdir);
  RemoveMacros((u16*)((u8*)prj + g->macroOff));
  RemoveCurves((u16*)((u8*)prj + g->curveOff));
  RemoveKeymaps((u16*)((u8*)prj + g->keymapOff));
  RemoveLayers((u16*)((u8*)prj + g->layerOff));
  if (g->type == 1) {
    RemoveFXTab(g->id);
  }
  return 1;
}

/*












*/

u32 seqPlaySong(u16 sgid, u16 sid, void* arrfile, SND_PLAYPARA* para, u8 irq_call, u8 studio) {
  int i;
  GROUP_DATA* g;
  PAGE* norm;
  PAGE* drum;
  MIDISETUP* midiSetup;
  u32 seqId;
  void* prj;
  DATA_STACK* stk;

  for (stk = dataStackRoot; stk != NULL; stk = stk->prev) {
    for (i = 0; i < stk->sp; ++i) {
      if (stk->gs[i].gAddr->id != sgid) {
        continue;
      }

      if (stk->gs[i].gAddr->type == 0) {
        g = stk->gs[i].gAddr;
        prj = stk->gs[i].prjAddr;
        norm = (PAGE*)((u32)prj + g->data.song.normpageOff);
        drum = (PAGE*)((u32)prj + g->data.song.drumpageOff);
        midiSetup = (MIDISETUP*)((u32)prj + g->data.song.midiSetupOff);
        while (midiSetup->songId != 0xFFFF) {
          if (midiSetup->songId == sid) {
            if (irq_call != 0) {
              seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
            } else {
              hwDisableIrq();
              seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
              hwEnableIrq();
            }
            return seqId;
          }

          ++midiSetup;
        }

        return 0xffffffff;
      } else {
        return 0xffffffff;
      }
    }
  }

  return 0xffffffff;
}

/* Inlined copy of seqPlaySong used by sndSeqPlayEx. */
static inline u32 seqPlaySongInline(u16 sgid, u16 sid, void* arrfile, SND_PLAYPARA* para, u8 irq_call,
                                    u8 studio) {
  int i;
  GROUP_DATA* g;
  PAGE* norm;
  PAGE* drum;
  MIDISETUP* midiSetup;
  u32 seqId;
  void* prj;
  DATA_STACK* stk;

  for (stk = dataStackRoot; stk != NULL; stk = stk->prev) {
    for (i = 0; i < stk->sp; ++i) {
      if (stk->gs[i].gAddr->id != sgid) {
        continue;
      }

      if (stk->gs[i].gAddr->type == 0) {
        g = stk->gs[i].gAddr;
        prj = stk->gs[i].prjAddr;
        norm = (PAGE*)((u32)prj + g->data.song.normpageOff);
        drum = (PAGE*)((u32)prj + g->data.song.drumpageOff);
        midiSetup = (MIDISETUP*)((u32)prj + g->data.song.midiSetupOff);
        while (midiSetup->songId != 0xFFFF) {
          if (midiSetup->songId == sid) {
            if (irq_call != 0) {
              seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
            } else {
              hwDisableIrq();
              seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
              hwEnableIrq();
            }
            return seqId;
          }

          ++midiSetup;
        }

        return 0xffffffff;
      } else {
        return 0xffffffff;
      }
    }
  }

  return 0xffffffff;
}

u32 sndSeqPlayEx(u16 sgid, u16 sid, void* arrfile, SND_PLAYPARA* para, u8 studio) {
  return seqPlaySongInline(sgid, sid, arrfile, para, 0, studio);
}