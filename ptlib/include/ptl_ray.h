#ifndef PTLIB_RAY_h
#define PTLIB_RAY_h

#include "ptl_vector.h"

struct Ray {
    struct Vec origin, direction;
};

struct Ray ray_init(struct Vec origin_, struct Vec direction_){
    struct Ray r;
    r.origin = origin_;
    r.direction = direction_;
    return r;
}

#endif //PTLIB_RAY_h