#ifndef PTLIB_UTIL_h
#define PTLIB_UTIL_h

#include "ptl_vector.h"
#include "ptl_ray.h"
#include "ptl_traceable_list.h"

#ifndef __OPENCL_VERSION__
#include <float.h>
#endif

inline PTNUM clamp(PTNUM x);

inline int to_int(PTNUM x);

inline int intersects(struct Ray *r, PTNUM *t, int *id, struct TraceableList *list);

#endif //PTLIB_UTIL_h