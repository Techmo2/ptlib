#ifndef PTLIB_SCENE_h
#define PTLIB_SCENE_h

#define PTLIB_MAX_DEPTH 5
#define PI 3.14159265

#include "ptl_traceable_list.h"
#include "ptl_image.h"

enum PTLIB_RENDER_DEV {
    PTLIB_GPU,
    PTLIB_CPU
};

struct Scene {
    struct TraceableList *items;
    enum PTLIB_RENDER_DEV device;

    unsigned int width;
    unsigned int height;

    struct Image* rendered;
};

void scene_free(struct Scene* s);

struct Scene* scene_new(unsigned int width_, unsigned int height_, enum PTLIB_RENDER_DEV render_device_);

void scene_add_tracable(struct Scene* scene, struct Traceable t);

struct Image* scene_render_from(struct Scene* scene, struct Ray *c, unsigned int samples, unsigned int width, unsigned int height);

#endif //PTLIB_SCENE_h