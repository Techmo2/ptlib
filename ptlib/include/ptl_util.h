#ifndef PTLIB_UTIL_h
#define PTLIB_UTIL_h

#include "ptl_vector.h"
#include "ptl_ray.h"
#include "ptl_traceable_list.h"
#include "ptl_list.h"
#include "ptl_scene.h"


#ifndef __OPENCL_VERSION__
#include <float.h>
#endif

PTNUM clamp(PTNUM x);
int to_int(PTNUM x);
int intersects(struct Ray *r, PTNUM *t, int *id, struct TraceableList *list);
int load_pt_scene_file(char* path, struct Scene* scene);

#endif //PTLIB_UTIL_h