#include "ptl_image.h"
#include <stdlib.h>

struct Image* image_new(unsigned int width, unsigned int height){
    struct Image *img;

    img = (struct Image*) malloc(sizeof(struct Image));

    img->data = (struct Vec**) malloc(sizeof(struct Vec*) * width);

    for(int i = 0; i < width; i++){
        img->data[i] = (struct Vec*) malloc(sizeof(struct Vec) * height);
    }

    img->width = width;
    img->height = height;

    return img;
}

void image_free(struct Image* image){
    for(int i = 0; i < image->width; i++){
        free(image->data[i]);
    }

    free(image->data);

    free(image);
}