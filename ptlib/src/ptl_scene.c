#include "ptl_scene.h"
#include "ptl_util.h"

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void scene_free(struct Scene* s){
    traceable_list_free(s->items);
    image_free(s->rendered);

    free(s);
}

struct Scene* scene_new(unsigned int width_, unsigned int height_, enum PTLIB_RENDER_DEV render_device_){
    struct Scene* s = (struct Scene*) malloc(sizeof(struct Scene));

    srand(time(NULL));

    s->width = width_;
    s->height = height_;
    s->device = render_device_;

    s->items = traceable_list_new(10);

    s->rendered = image_new(width_, height_);

    return s;
}

void scene_add_traceable(struct Scene* scene, struct Traceable t){
    traceable_list_push(t, scene->items);
}

PTNUM luma(struct Vec color){
    return dot(color, vec_init(0.2126f, 0.7152f, 0.0722f));
}

PTNUM ptrandom(){
    PTNUM r = (PTNUM) rand() / (PTNUM) RAND_MAX;
    return r;
}

struct Vec radiance(struct Ray r, int depth, struct TraceableList* list){
    if(depth > PTLIB_MAX_DEPTH) return vec_init_e();

    PTNUM t;
    int id = 0;

    // If no hit, return black
    if(!intersects(&r, &t, &id, list)){

        return vec_init_e();
    }

    struct Traceable *obj = &(list->elements[id]);

    //fprintf(stdout, "ID: %d  POS: %f %f %f\n", id, obj->position.x, obj->position.y, obj->position.z);

    struct Vec x = vec_add(r.origin, vec_mult(r.direction, t));
    //fprintf(stdout, "X: %f %f %f  ORG: %f %f %f  T: %f\n", x.x, x.y, x.z, r.origin.x, r.origin.y, r.origin.z, t);

    // Get normal
    struct Vec n = obj->normal(*obj, x);
    //fprintf(stdout, "Normal: %f %f %f\n", n.x, n.y, n.z);

    // Get corrext normal, flip if ray is on inside
    struct Vec nl = dot(n, r.direction) < 0 ? n : vec_mult(n, -1);

    // Albedo
    struct Vec albedo = obj->color;

    //fprintf(stdout, "Albedo: %f %f %f\n", albedo.r, albedo.g, albedo.b);

    PTNUM rrprobability = luma(albedo);

    //fprintf(stdout, "Prob: %f\n", rrprobability);


    if(++depth > 5){
        //fprintf(stdout, "Rand: %f\n", ptrandom());

        if(ptrandom() < rrprobability){
            albedo = vec_div(albedo, rrprobability);
            //fprintf(stdout, "DIV Albedo: %f %f %f\n", albedo.r, albedo.g, albedo.b);
        }
        else{
            return obj->emission;
        }
    }

    if(obj->material.type == PTMAT_DIFFUSE){
        PTNUM phi = 2 * PI * ptrandom();
        PTNUM r2 = ptrandom();
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

struct Vec* scene_render_from(struct Scene* scene, struct Ray c, unsigned int samples, unsigned int width, unsigned int height){

    int samps = samples / 4;

    PTNUM aspect_ratio = (PTNUM)(width) / (PTNUM)(height);
    PTNUM fov = 0.502643; // 58 degree fov
    PTNUM fov_scale = 2 * tan(0.5 * fov);

    struct Vec r = vec_init_e();

    struct Vec cx = vec_mult(vec_init(aspect_ratio, 0, 0), fov_scale);
    struct Vec cy = vec_mult(vec_norm(vec_cross(cx, c.direction)), fov_scale);

    struct Vec* image = (struct Vec*) malloc(sizeof(struct Vec) * width * height);

    fprintf(stdout, "CX: %f %f %f\n", cx.x, cx.y, cx.z);
    fprintf(stdout, "CY: %f %f %f\n", cy.x, cy.y, cy.z);

    fprintf(stdout, "CAM: %f %f %f\n", c.origin.x, c.origin.y, c.origin.z);

    for(int y = 0; y < height; ++y){
        fprintf(stderr, "\r Rendering (%d spp) %5.2f%%", samples, 100.0 * y/(height - 1));
        for(unsigned short x = 0; x < width; ++x){
            // 2x2 subpixel rows
            for(int sy = 0, i = (height - y - 1) * width + x; sy < 2; ++sy){
                // 2x2 subpixel cols
                for(int sx = 0; sx < 2; sx++, r = vec_init_e()){
                    // samples per subpixel
                    for(int s = 0; s < samps; s++){
                        PTNUM r1 = 2.0 * ptrandom();
                        
                        PTNUM dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
						PTNUM r2 = 2.0 * ptrandom();
						PTNUM dy;

                        if(r2 < 1.0){
                            dy = (PTNUM) (sqrt(r2)) - 1.0;
                        }
                        else{
                            dy = 1.0 - (PTNUM) (sqrt(2.0 - r2));
                        }

                        //fprintf(stdout, "DX: %f  DY: %f  R2: %f  R1: %f\n", dx, dy, r2, r1);

                        // Get primary ray direction
                        struct Vec d = vec_add(
                            vec_mult(
                                cx,
                                (((sx + 0.5 + dx) / 2.0 + x) / width - 0.5)
                            ),
                            vec_add(
                                vec_mult(
                                    cy,
                                    (((sy + 0.5 + dy) / 2.0 + y) / height - 0.5)
                                ),
                                c.direction
                            )
                        );

                        //fprintf(stdout, "D: %f %f %f\n", d.x, d.y, d.z);

                        struct Ray cam_n = ray_init(
                            vec_add(
                                c.origin,
                                vec_mult(
                                    d,
                                    140
                                )
                            ),
                            vec_norm(d)
                        );

                        //fprintf(stdout, "CAM_N: %f, %f, %f    %f, %f %f\n", cam_n.origin.x, cam_n.origin.y, cam_n.origin.z, cam_n.direction.x, cam_n.direction.y, cam_n.direction.z);

                        r = vec_add(
                            r,
                            vec_mult(
                                radiance(
                                    cam_n,
                                    0,
                                    scene->items
                                ),
                                (1.0 / samps)
                            )
                        );

                        //fprintf(stdout, "R: %f %f %f\n", r.r, r.g, r.b);
                    }

                    image[i] = vec_add(
                        image[i],
                        vec_mult(
                            vec_init(clamp(r.x), clamp(r.y), clamp(r.z)),
                            0.25
                        )
                    );
                }
            }
        }
    } 

    return image;
}