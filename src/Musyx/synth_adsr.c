
#include "musyx/musyx_priv.h"
#include "musyx/synth_dbtab.h"

#include <float.h>

extern double pow(double, double);

static u32 adsrGetIndex(ADSR_VARS* adsr) {
  s32 i = 193 - ((adsr->currentIndex + 0x8000) >> 16);
  return i < 0 ? 0 : i;
}

u32 adsrConvertTimeCents(long tc) { return 1000.f * (f32)pow(2.0, 1.2715658e-08f * tc); }

u32 salChangeADSRState(ADSR_VARS* adsr) {
  u32 VoiceDone = 0;

  switch (adsr->mode) {
  case 0:
    switch (adsr->state) {
    case 0:
      if ((adsr->cnt = adsr->data.linear.aTime) != 0) {
        adsr->state = 1;
        adsr->currentVolume = 0;
        adsr->currentDelta = 0x7FFF0000 / adsr->data.linear.aTime;
        break;
      }
    case 1:
      if ((adsr->cnt = adsr->data.linear.dTime) != 0) {
        adsr->state = 2;
        adsr->currentVolume = 0x7FFF0000;
        adsr->currentDelta =
            -((0x7FFF0000 - (adsr->data.linear.sLevel << 16)) / adsr->data.linear.dTime);
        break;
      }
    case 2:
      if (adsr->data.linear.sLevel != 0) {
        adsr->state = 3;
        adsr->currentVolume = adsr->data.linear.sLevel << 16;
        adsr->currentDelta = 0;
        break;
      }
    case 4:
      VoiceDone = 1;
      adsr->currentVolume = 0;
      break;
    }
    break;
  case 1:
    switch (adsr->state) {
    case 0:
      if ((adsr->cnt = adsr->data.dls.aTime) != 0) {
        adsr->state = 1;
        if (adsr->data.dls.aMode == 0) {
          adsr->currentVolume = 0;
          adsr->currentDelta = 0x7FFF0000 / adsr->cnt;
        } else {
          adsr->currentIndex = 0;
          adsr->currentVolume = 0;
          adsr->currentDelta = 0xC10000 / adsr->cnt;
        }
        break;
      }
    case 1:
      adsr->cnt = (adsr->data.dls.dTime * ((u32)((193 - adsr->data.dls.sLevel) << 16) / 193)) >> 16;
      if (adsr->cnt != 0) {
        adsr->state = 2;
        adsr->currentVolume = 0x7FFF0000;
        adsr->currentIndex = 0xC10000;
        adsr->currentDelta = -(((193 - adsr->data.dls.sLevel) << 16) / adsr->cnt);
        break;
      }
    case 2:
      if (adsr->data.dls.sLevel != 0) {
        adsr->state = 3;
        adsr->currentIndex = adsr->data.dls.sLevel << 16;
        adsr->currentVolume = dspAttenuationTab[adsrGetIndex(adsr)] << 16;
        adsr->currentDelta = 0;
        break;
      }
    case 4:
      VoiceDone = 1;
      adsr->currentVolume = 0;
      break;
    }
    break;
  }

  return VoiceDone;
}

u32 adsrSetup(ADSR_VARS* adsr) {
  adsr->state = 0;
  return salChangeADSRState(adsr);
}

u32 adsrStartRelease(ADSR_VARS* adsr, u32 rtime) {
  switch (adsr->mode) {
  case 0:
    adsr->state = 4;
    adsr->cnt = rtime;
    if (rtime == 0) {
      adsr->cnt = 1;
      adsr->currentDelta = 0;
      return 1;
    }
    adsr->currentDelta = -(adsr->currentVolume / rtime);
    break;
  case 1:
    if (adsr->data.dls.aMode == 0 && adsr->state == 1) {
      adsr->currentIndex = (193 - dspScale2IndexTab[adsr->currentVolume >> 21]) * 0x10000;
    }

    adsr->cnt = (u32)(3.238342E-4f * (float)adsr->currentIndex * (float)rtime) >> 12;
    adsr->state = 4;
    if (adsr->cnt == 0) {
      adsr->cnt = 1;
      adsr->currentDelta = adsr->currentIndex = adsr->currentVolume = 0;
      return 1;
    }

    adsr->currentDelta = -(adsr->currentIndex / adsr->cnt);
    break;
  }

  return 0;
}

u32 adsrRelease(ADSR_VARS* adsr) {
  switch (adsr->mode) {
  case 0:
  case 1:
    return adsrStartRelease(adsr, adsr->data.dls.rTime);
  }

  return FALSE;
}

u32 adsrHandle(ADSR_VARS* adsr, u16* adsr_start, u16* adsr_delta) {
  s32 old_volume;
  s32 vDelta;
  u32 VoiceDone = 0;

  switch (adsr->mode) {
  case 0:
    if (adsr->state != 3) {
      old_volume = adsr->currentVolume;
      adsr->currentVolume += adsr->currentDelta;
      *adsr_start = old_volume >> 16;
      if (adsr->currentDelta >= 0) {
        *adsr_delta = adsr->currentDelta >> 21;
      } else {
        *adsr_delta = -(-adsr->currentDelta >> 21);
      }
      if (--adsr->cnt == 0) {
        VoiceDone = salChangeADSRState(adsr);
      }
    } else {
      *adsr_start = adsr->currentVolume >> 16;
      *adsr_delta = 0;
    }
    break;
  case 1:
    if (adsr->state != 3) {
      old_volume = adsr->currentVolume;
      if (adsr->data.dls.aMode == 0 && adsr->state == 1) {
        adsr->currentVolume += adsr->currentDelta;
      } else {
        adsr->currentIndex += adsr->currentDelta;
        adsr->currentVolume = dspAttenuationTab[adsrGetIndex(adsr)] << 16;
      }
      *adsr_start = old_volume >> 16;
      vDelta = adsr->currentVolume - old_volume;
      if (vDelta >= 0) {
        *adsr_delta = vDelta >> 21;
      } else {
        *adsr_delta = -(-vDelta >> 21);
      }
      if (--adsr->cnt == 0) {
        VoiceDone = salChangeADSRState(adsr);
      }
    } else {
      *adsr_start = adsr->currentVolume >> 16;
      *adsr_delta = 0;
    }
    break;
  }
  return VoiceDone;
}

u32 adsrHandleLowPrecision(ADSR_VARS* adsr, u16* adsr_start, u16* adsr_delta) {
  u8 i; // r31

  for (i = 0; i < 15; ++i) {
    if (adsrHandle(adsr, adsr_start, adsr_delta)) {
      return 1;
    }
  }

  return 0;
}
