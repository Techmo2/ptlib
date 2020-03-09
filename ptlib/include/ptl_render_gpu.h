#ifndef PTLIB_RENDER_GPU_h
#define PTLIB_RENDER_GPU_h

#include "ptl_scene.h"
#include "ptl_ray.h"
#include "ptl_radiance.h"

struct Vec* scene_render_gpu(struct Scene* scene, struct Ray c, unsigned int samples, unsigned int width, unsigned int height, int(*progress_callback)(int current_row, int total_rows));

#endif // PTLIB_RENDER_GPU_h