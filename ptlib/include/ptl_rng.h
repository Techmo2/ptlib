#ifndef PTLIB_RNG_h
#define PTLIB_RNG_h

#define FMASK (1 << 23) - 1

struct RNG {
    unsigned int x;
};

struct RNG* rng_new(unsigned int seed);

int rng_next_i(struct RNG* rng);

float rng_next_f(struct RNG* rng);

void rng_free(struct RNG* rng);

#endif //PTLIB_RNG_h