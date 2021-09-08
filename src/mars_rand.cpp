/*
 *  mars_rand.cpp
 *  Definitions for additional RNG function overrides
 */
#ifndef MARS_EXPORTS
#define MARS_EXPORTS
#endif
#include "mars_rand.hpp"

namespace mars {

void rng_seed(uint32_t seed) {
  #if defined(MARS_RNG_MWC)
    mwc_z = seed;
    mwc_w = 521288629;
  #elif defined(MARS_RNG_STD)
    srand(seed);
  #endif
}

}