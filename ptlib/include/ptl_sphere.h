#ifndef PTL_SPHERE_h
#define PTL_SPHERE_h

#include "ptl_traceable.h"
#include "ptl_config.h"

/* Intersect function for a tracable sphere */
PTNUM sphere_intersect(struct Ray *r, struct TraceableObject *tb);

/* Function to get the normal at a given point */
struct Vec sphere_normal(struct TraceableObject t, struct Vec x);

struct TraceableObject sphere_init(PTNUM radius_, struct Vec position_, struct Vec emission_, struct Vec color_, struct Material material_);

#endif //PTL_SPHERE_h