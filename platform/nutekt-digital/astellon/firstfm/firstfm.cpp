#include "userosc.h"
#include "firstfm.hpp"

static FirstFM firstfm;

void OSC_INIT(uint32_t platform, uint32_t api)
{
  firstfm.init();
}

void OSC_CYCLE(const user_osc_param_t * const params,
               int32_t *yn,
               const uint32_t frames)
{
  q31_t * __restrict y = (q31_t *)yn;
  const q31_t * y_e = y + frames;

  firstfm.set_pitch(params->pitch);

  uint32_t i = 0;
  for (i = 0; i < frames; i++) {
    y[i] = f32_to_q31(firstfm.get());
    firstfm.advance();
  }
}

void OSC_NOTEON(const user_osc_param_t * const params)
{
  // NOTE ON
}

void OSC_NOTEOFF(const user_osc_param_t * const params)
{
  // NOTE OFF
}

void OSC_PARAM(uint16_t index, uint16_t value)
{
  switch (index)
  {
    case k_user_osc_param_id1:
      firstfm.ratio_ = clip01f(value * 0.02f);
      break;
    case k_user_osc_param_id2:
      firstfm.gain_ = clip01f(value * 0.01f);
      break;
    case k_user_osc_param_id3:
      break;
    case k_user_osc_param_id4:
      break;
    case k_user_osc_param_id5:
      break;
    case k_user_osc_param_id6:
      break;
    default:
      break;
  }
}
