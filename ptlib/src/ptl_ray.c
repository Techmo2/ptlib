#include "ptl_ray.h"

struct Ray ray_init(struct Vec origin_, struct Vec direction_){
    struct Ray r;
    r.origin = origin_;
    r.direction = direction_;
    return r;
}