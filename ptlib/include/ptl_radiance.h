#ifndef PTL_RADIANCE_h
#define PTL_RADIANCE_h

#include "ptl_vector.h"
#include "ptl_ray.h"
#include "ptl_traceable_list.h"
#include "ptl_rng.h"

PTNUM luma(struct Vec color);
struct Vec radiance(struct Ray r, int depth, struct TraceableList* list);

#endif // PTL_RADIANCE_h