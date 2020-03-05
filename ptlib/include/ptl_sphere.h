#ifndef PTL_SPHERE_h
#define PTL_SPHERE_h

#include "ptl_traceable.h"

/* Intersect function for a tracable sphere */
PTNUM sphere_intersect(struct Ray *r, struct Traceable *tb){
        struct Vec op = vec_sub(tb->position, r->origin);

        PTNUM t;
        PTNUM eps = 1e-4;
        PTNUM b = dot(op, r->direction);

        PTNUM det = b * b - dot(op, op) + tb->properties.v1 * tb->properties.v1;

        if (det < 0){
            return 0;
        }
        else {
            det = sqrt(det);
        }

        t = b - det;

        if(t > eps){
            return t;
        }
        else {
            t = b + det;

            if(t > eps){
                return t;
            }
            
            return 0;
        }
}

/* Function to get the normal at a given point */
struct Vec sphere_normal(struct Traceable *t, struct Vec x){
    return vec_div(vec_sub(x, t->position), t->properties.v1);
}

/* A tracable sphere. We store its radius in tracable property 1, and set intersect to that for a sphere */
struct Sphere {
    struct Traceable traceable;
};

struct Traceable sphere_init(PTNUM radius_, struct Vec position_, struct Vec emission_, struct Vec color_, struct Material material_){
    struct Traceable traceable;

    traceable.position = position_;
    traceable.emission = emission_;
    traceable.color = color_;
    traceable.material = material_;

    traceable.properties.v1 = radius_;
    traceable.intersect = sphere_intersect;
    traceable.normal = sphere_normal;

    return traceable;
}

#endif //PTL_SPHERE_h