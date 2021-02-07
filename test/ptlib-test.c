#include "ptl_vector.h"
#include "ptl_scene.h"
#include "ptl_sphere.h"
#include "ptl_util.h"
#include "ptl_list.h"
#include "ptl_loader.h"
#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>

#define BMP_PADDING_SIZE(r) ((r) % 4)

int progress_callback(int current_row, int total_rows){
    fprintf(stdout, "\rRendering: %5.2f%%  (%d/%d)", 100.f * ((float) current_row / (float)(total_rows - 1)), current_row, total_rows);
}

int main(int argc, char** argv){
    int width = 640;
    int height = 480;
    int samples = 64;

    /* Create a new scene to store ourTraceableObjectobjects */
    struct Scene* scene = scene_new(width, height, PTLIB_CPU);

    /* LoadTraceableObjectspheres from a text file */
    /* They may also be hard coded in, but this is not recommended */
    load_pt_scene_file("example.pts", scene);

    /* Define the camera. The camera is a simple Ray with an origin, and a direction */
    struct Ray camera = ray_init(vec_init(50, 52, 290.6), vec_norm(vec_init(0, -0.042612, -1)));

    /* Render a scene, providing a callback function to be used for progress updates */
    /* The rendered scene will be returned as an array of vectors with a length of (width * height) */
    struct Vec* rendered = scene_render_from(scene, camera, samples, width, height, &progress_callback);
    
    /* Lets write the output to a bitmap file to make it easier to see the output */    
    bmp_img img;
    bmp_img_init_df(&img, width, height);

    for(int i = 0; i < width * height; i++){
        int x = i % width;
        int y = i / width;

        PTNUM r;
        PTNUM g;
        PTNUM b;

        r = to_int(rendered[i].r);
        g = to_int(rendered[i].g);
        b = to_int(rendered[i].b);

        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;

        bmp_pixel_init(&img.img_pixels[y][x], r, g, b);
    }

    bmp_img_write(&img, "output.bmp");
    bmp_img_free(&img);

    scene_free(scene);
}