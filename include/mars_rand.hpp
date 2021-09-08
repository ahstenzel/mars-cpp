/*
 *  mars_rand.hpp
 *  Declarations for additional RNG function overrides
 */
#pragma once

#include "mars_core.hpp"

namespace mars {

#define MARS_RNG_STD		// Declare which RNG system to use
//#define MARS_RNG_MWC

#if defined(MARS_RNG_MWC)
/*=======================================================*/
/* MWC                                                   */
/* Multiply-with-carry. Fast and simple, but not the     */
/* most robust.                                          */
/*=======================================================*/
  static uint32_t mwc_z = 362436069;
  static uint32_t mwc_w = 521288629;
  #define MWC_ZNEW (mwc_z=36969*(mwc_z&65535)+(mwc_z>>16))
  #define MWC_WNEW (mwc_w=18000*(mwc_w&65535)+(mwc_z>>16))
  #define MWC ((MWC_ZNEW<<16)+MWC_WNEW)
  #define MRAND MWC
#elif defined(MARS_RNG_STD)
/*=======================================================*/
/* std                                                   */
/* Use the standard C rand() function.                   */
/*=======================================================*/
  #define MRAND rand()
#endif

void MARS_API rng_seed(uint32_t seed);

}