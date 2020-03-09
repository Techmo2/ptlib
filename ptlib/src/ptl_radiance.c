#include "ptl_radiance.h"
#include "ptl_util.h"

PTNUM luma(struct Vec color){
    return dot(color, vec_init(0.2126f, 0.7152f, 0.0722f));
}

inline struct Vec radiance(struct Ray r, int depth, struct TraceableList* list){
    if(depth > MAX_TRACE_DEPTH) return vec_init_e();

    PTNUM t;
    int id = 0;

    // If no hit, return black
    if(!intersects(&r, &t, &id, list)){

        return vec_init_e();
    }

    struct Traceable *obj = &(list->elements[id]);
    struct Vec x = vec_add(r.origin, vec_mult(r.direction, t));

    // Get normal
    struct Vec n = obj->normal(*obj, x);

    // Get corrext normal, flip if ray is on inside
    struct Vec nl = dot(n, r.direction) < 0 ? n : vec_mult(n, -1);

    // Albedo
    struct Vec albedo = obj->color;

    PTNUM rrprobability = luma(albedo);

    if(++depth > 5){

        if(rng_next() < rrprobability){
            albedo = vec_div(albedo, rrprobability);
        }
        else{
            return obj->emission;
        }
    }

    if(obj->material.type == PTMAT_DIFFUSE){
        PTNUM phi = 2 * PI * rng_next();
        PTNUM r2 = rng_next();
        PTNUM sinTheta = sqrt(r2);
        PTNUM cosTheta = sqrt(1 - r2);

        struct Vec w = nl;

        struct Vec u = vec_norm(vec_cross(fabs(w.x) > 0.1 ? vec_init(0, 1, 0) : vec_init(1, 0, 0), w));
        struct Vec v = vec_cross(w, u);

        struct Vec d = vec_norm(

            vec_add(
            vec_add(
            vec_mult(vec_mult(u,cos(phi)), sinTheta),
            vec_mult(vec_mult(v, sin(phi)),sinTheta)
            ),
            vec_mult(w, cosTheta)
            )
        );

        struct Vec ret = vec_add(
            obj->emission,
            vec_multv(
                albedo,
                radiance(ray_init(x, d), depth, list)
            )
        );

        return ret;
    }
    else if(obj->material.type == PTMAT_SPECULAR){
        struct Vec refl = vec_sub(
            r.direction,
            vec_mult(
                n, 
                2 * dot(n, r.direction)
            )
        );

        struct Vec ret = vec_add(
            obj->emission,
            vec_multv(
                albedo,
                radiance(ray_init(x, refl), depth, list)
            )
        );

        return ret;
    }
    else if(obj->material.type == PTMAT_REFRACT){
        // TODO: Implement refract
    }
    else{
        // Unknwon material
    }
}