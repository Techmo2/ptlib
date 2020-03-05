#ifndef PTLIB_IMAGE_h
#define PTLIB_IMAGE_h

#include "ptl_vector.h"

struct Image {
    unsigned int height;
    unsigned int width;
    struct Vec** data;
};

struct Image* image_new(unsigned int width, unsigned int height);
void image_free(struct Image* image);

#endif //PTLIB_IMAGE_h