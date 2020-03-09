#include "ptl_scene.h"
#include "ptl_util.h"
#include "ptl_config.h"
#include "ptl_rng.h"
#include "ptl_render_cpu.h"
#include "ptl_render_gpu.h"

#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef ENABLE_OPENMP
#include <omp.h>
#endif

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

struct Vec* scene_render_from(struct Scene* scene, struct Ray c, unsigned int samples, unsigned int width, unsigned int height, int(*progress_callback)(int current_row, int total_rows)){
    struct Vec* image;

    switch(scene->device){
        case PTLIB_CPU:
            image = scene_render_cpu(scene, c, samples, width, height, progress_callback);
        break;

        case PTLIB_GPU:
            image = scene_render_gpu(scene, c, samples, width, height, progress_callback);
        break;

        default:
            // Default to CPU
            image = scene_render_cpu(scene, c, samples, width, height, progress_callback);
        break;
    }

    return image;
}