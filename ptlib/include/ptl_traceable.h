/*

Author: Bradly Tillmann

This struct represents aTraceableObjectobject, and contains all information needed for
path tracing. This should be returned by anyTraceableObjectobjects you wish to add.

*/

#ifndef PTL_TRACEABLE_h
#define PTL_TRACEABLE_h

#include "ptl_material.h"
#include "ptl_vector.h"
#include "ptl_ray.h"


/* Holds object properties that may be different for each type. Radius for example. */
struct Properties {
    union {
        PTNUM values[9];

        struct {
            PTNUM v1;
            PTNUM v2;
            PTNUM v3;
            PTNUM v4;
            PTNUM v5;
            PTNUM v6;
            PTNUM v7;
            PTNUM v8;
            PTNUM v9;
        };
    };
};


struct TraceableObject {
    struct Vec position;
    struct Vec emission;
    struct Vec color;

    struct Material material;
    struct Properties properties;

    /* Determines if an intersection would occur, should be implemented by children */
    PTNUM (*intersect)(struct Ray *r, struct TraceableObject *tb);

    /* Computes the normal at the given intersection point */
    struct Vec (*normal)(struct TraceableObject t, struct Vec x);
};

struct TraceableObject traceable_init(struct Properties properties_, struct Vec position_, struct Vec emission_, struct Vec color_, struct Material material_, PTNUM (*intersect_)(struct Ray *r, struct TraceableObject *tb));

struct TraceableObject traceable_init_e();

#endif //PTL_TRACEABLE_h