/*

Author: Bradly Tillmann

This struct represents a tracable object, and contains all information needed for
path tracing. This should be returned by any tracable objects you wish to add.

*/

#ifndef PTL_TRACEABLE_h
#define PTL_TRACEABLE_h

#include "ptl_material.h"
#include "ptl_vector.h"
#include "ptl_ray.h"


/* Holds object properties that may be different for each type. Radius for example. */
struct Properties {
    union {
        PTNUM values[5];

        struct {
            PTNUM v1;
            PTNUM v2;
            PTNUM v3;
            PTNUM v4;
            PTNUM v5;
        };
    };
};


struct Traceable {
    struct Vec position;
    struct Vec emission;
    struct Vec color;

    struct Material material;
    struct Properties properties;

    /* Determines if an intersection would occur, should be implemented by children */
    PTNUM (*intersect)(struct Ray *r, struct Traceable *tb);

    /* Computes the normal at the given intersection point */
    struct Vec (*normal)(struct Traceable *t, struct Vec x);
};

struct Traceable traceable_init(struct Properties properties_, struct Vec position_, struct Vec emission_, struct Vec color_, struct Material material_, PTNUM (*intersect_)(struct Ray *r, struct Traceable *tb)){
    struct Traceable t;
    t.properties = properties_;
    t.position = position_;
    t.emission = emission_;
    t.color = color_;
    t.material = material_;
    t.intersect = intersect_;

    return t;
}

struct Traceable traceable_init_e(){
    struct Traceable t;
    struct Properties p;

    t.properties = p;
    t.position = vec_init_e();
    t.emission = vec_init_e();
    t.color = vec_init_e();
    t.material = material_init();

    t.intersect = 0;

    return t;
}

#endif //PTL_TRACEABLE_h