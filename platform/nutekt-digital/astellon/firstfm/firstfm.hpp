#pragma once

#include "userosc.h"

struct FirstFM
{
  FirstFM()
  {
    init();
  }

  void init()
  {
    phase1_ = 0.0f;
    phase2_ = 0.0f;
    angle_delta1_ = 0.0f;
    angle_delta2_ = 0.0f;
    ratio_ = 1.0f;
    gain_  = 1.0f;
  }

  float get()
  {
    return osc_sinf(phase1_);
  }

  float set_pitch(uint16_t pitch)
  {
    angle_delta1_ = osc_w0f_for_note(pitch>>8, pitch&0xFF);
    angle_delta2_ = angle_delta1_ * ratio_;
  }

  void advance()
  {
    phase1_ += angle_delta1_ * ( 1 + osc_sinf(phase2_) * gain_ );
    phase2_ += angle_delta2_;

    phase1_ -= (uint16_t)phase1_;
    phase2_ -= (uint16_t)phase2_;
  }

  float phase1_;
  float phase2_;
  float angle_delta1_;
  float angle_delta2_;
  float ratio_;
  float gain_;
};
