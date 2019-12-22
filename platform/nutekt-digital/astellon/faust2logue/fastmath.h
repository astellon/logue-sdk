#ifndef __FASTMATH_H__
#define __FASTMATH_H__

#include "../../inc/utils/float_math.h"

static inline __attribute__((optimize("Ofast"), always_inline))
inline float fast_sqrtf( const float x )
{
  float xHalf = 0.5f * x;
  int   tmp   = 0x5F3759DF - ( *(int*)&x >> 1 ); //initial guess
  float xRes  = *(float*)&tmp;

  xRes *= ( 1.5f - ( xHalf * xRes * xRes ) );
  return xRes * x;
}

static inline __attribute__((optimize("Ofast"), always_inline))
inline float fast_sinf( const float x ) {
  if (x > M_PI) {
    return -1.0 * fast_sinf(x - M_PI);
  } else if (x < 0) {
    return -1.0 * fast_sinf(-x);
  } else {
    return fastsinf(x);
  }
  return 0;
}

static inline __attribute__((optimize("Ofast"), always_inline))
inline float fast_cosf( const float x ) {
  return fast_sinf(M_PI_2 - x);
}

#endif