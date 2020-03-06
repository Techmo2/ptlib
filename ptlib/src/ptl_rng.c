#include "ptl_rng.h"
#include <malloc.h>

struct RNG* rng_new(unsigned int seed){
    struct RNG* rng = (struct RNG*) malloc(sizeof(struct RNG));
    rng->x = seed;
    return rng;
}

int rng_next_i(struct RNG* rng){
    rng->x ^= rng->x >> 6;
    rng->x ^= rng->x << 17;
    rng->x ^= rng->x >> 9;
    return (int)(rng->x);
}

float rng_next_f(struct RNG* rng){
    union {
        float f;
        int i;
    } u;

    u.i = (rng_next_i(rng) & FMASK | 0x3f800000);
    return u.f - 1.0f;
}

void rng_free(struct RNG* rng);
