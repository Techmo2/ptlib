#include "ptl_radiance.h"
#include "ptl_util.h"

PTNUM luma(struct Vec color){
    return vec_dot(color, vec_init(0.2126f, 0.7152f, 0.0722f));
}

inline struct Vec radiance(struct Ray r, int depth, struct TraceableList* list){
    if(depth > MAX_TRACE_DEPTH) return vec_init_e();

    PTNUM t;
    int id = 0;

    // If no hit, return black
    if(!intersects(&r, &t, &id, list)){

        return vec_init_e();
    }

    struct TraceableObject *obj = &(list->elements[id]);

    // Intersection point
    struct Vec x = vec_add(r.origin, vec_mult(r.direction, t));

    // Get normal
    struct Vec n = obj->normal(*obj, x);

    // Get corrext normal, flip if ray is on inside
    struct Vec nl = vec_dot(n, r.direction) < 0.0 ? n : vec_mult(n, -1.0);

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
                2 * vec_dot(n, r.direction)
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

        struct Ray relfR = ray_init(
            x,
            vec_sub(
            r.direction,
                vec_mult(
                    n, 
                    2.0 * vec_dot(n, r.direction)
                )
            )
        );

        int going_in = vec_dot(n, nl) > 0.0;

        PTNUM nc = 1.0;
        PTNUM nt = 1.5;
        PTNUM nnt;


        if(going_in){
            nnt = nc / nt;
        }
        else{
            nnt = nt / nc;
        }


        PTNUM cosT = vec_dot(r.direction, nl);
        PTNUM cosTS = 1.0 - nnt * nnt * (1.0 - cosT * cosT);


        // Total internal reflection
        if(cosTS < 0){
            return vec_add(
                obj->emission,
                vec_multv(
                    albedo,
                    radiance(relfR, depth, list)
                )
            );
        }


        PTNUM tdir_t = cosT * cosT + sqrt(cosTS);
        if(!going_in)
            tdir_t *= -1.0;

        struct Vec tdir = vec_norm(
            vec_sub(
                vec_mult(
                    r.direction,
                    nnt
                ),
                vec_mult(
                    n,
                    tdir_t
                )
            )
        );

        // Fresnel approximation
        PTNUM a = nt - nc;
        PTNUM b = nt + nc;
        PTNUM R0 = a * a / (b * b);
        PTNUM cosT2 = vec_dot(tdir, n);
        
        PTNUM c;
        if(going_in){
            c = 1 + cosT;
        }
        else {
            c = 1 - cosT2; 
        }

        // Weight of reflection
        PTNUM Re = R0 + (1.0 - R0) * c * c * c * c * c;

        // Wight of refraction     
        PTNUM Tr = 1.0 - Re;

        // Probability of reflection
        PTNUM P = 0.25 + 0.5 * Re;

        PTNUM RP = Re / P;
        PTNUM TP = Tr / (1 - P);

        // Splitting below depth 3
        if (depth < 3){
            return vec_add(
                obj->emission,
                vec_multv(
                    albedo,
                    vec_add(
                        vec_mult(
                            radiance(relfR, depth, list),
                            Re
                        ),
                        vec_mult(
                            radiance(
                                ray_init(
                                    x,
                                    tdir
                                ),
                                depth,
                                list
                            ),
                            Tr
                        )
                    )
                )
            );
        }
        else{
            if(rng_next() < P){
                return vec_add(
                    obj->emission,
                    vec_multv(
                        albedo,
                        vec_mult(
                            radiance(relfR, depth, list),
                            RP
                        )
                    )
                );
            }
            return vec_add(
                    obj->emission,
                    vec_multv(
                        albedo,
                        vec_mult(
                            radiance(
                                ray_init(
                                    x, 
                                    tdir
                                ),
                                depth,
                                list
                            ),
                            TP
                        )
                    )
                );
        }
    }
    else{
        // Unknwon material
    }
}