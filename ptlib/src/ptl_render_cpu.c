#include "ptl_render_cpu.h"
#include "ptl_radiance.h"
#include "ptl_util.h"

#include <math.h>
#include <malloc.h>
#include <stdlib.h>

struct Vec* scene_render_cpu(struct Scene* scene, struct Ray c, unsigned int samples, unsigned int width, unsigned int height, int(*progress_callback)(int current_row, int total_rows)){
    int samps = samples / 4;

    PTNUM aspect_ratio = (PTNUM)(width) / (PTNUM)(height);
    PTNUM fov = 0.502643; // 58 degree fov
    PTNUM fov_scale = 2 * tan(0.5 * fov);

    struct Vec r = vec_init_e();

    struct Vec cx = vec_mult(vec_init(aspect_ratio, 0, 0), fov_scale);
    struct Vec cy = vec_mult(vec_norm(vec_cross(cx, c.direction)), fov_scale);

    struct Vec* image = (struct Vec*) malloc(sizeof(struct Vec) * width * height);

    #ifdef ENABLE_OPENMP
    #pragma omp parallel for schedule(dynamic, 1) private(r)
    #endif

    for(int y = 0; y < height; ++y){
        (*progress_callback)(y, height);
        for(unsigned short x = 0; x < width; ++x){
            rng_new();

            // 2x2 subpixel rows
            for(int sy = 0, i = (height - y - 1) * width + x; sy < 2; ++sy){
                // 2x2 subpixel cols
                for(int sx = 0; sx < 2; sx++, r = vec_init_e()){
                    // samples per subpixel
                    for(int s = 0; s < samps; s++){
                        PTNUM r1 = 2.0 * rng_next();
                        
                        PTNUM dx = r1 < 1 ? sqrt(r1) - 1 : 1 - sqrt(2 - r1);
						PTNUM r2 = 2.0 * rng_next();
						PTNUM dy;

                        if(r2 < 1.0){
                            dy = (PTNUM) (sqrt(r2)) - 1.0;
                        }
                        else{
                            dy = 1.0 - (PTNUM) (sqrt(2.0 - r2));
                        }


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