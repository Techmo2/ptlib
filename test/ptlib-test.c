#include "ptl_scene.h"
#include "ptl_sphere.h"
#include "ptl_util.h"
#include "ptl_list.h"
#include <stdio.h>

int progress_callback(int current_row, int total_rows){
    fprintf(stdout, "\rRendering: %5.2f%%  (%d/%d)", 100.f * ((float) current_row / (float)(total_rows - 1)), current_row, total_rows);
}

int main(int argc, char** argv){
    int width = 640;
    int height = 480;
    int samples = 128;

    struct Scene* scene = scene_new(width, height, PTLIB_CPU);

    load_pt_scene_file("example.pts", scene);

    struct Ray camera = ray_init(vec_init(50, 52, 290.6), vec_norm(vec_init(0, -0.042612, -1)));

    struct Vec* rendered = scene_render_from(scene, camera, samples, width, height, &progress_callback);
    
    FILE *f = fopen("output.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);

    for(int i = 0; i < width * height; i++){
        fprintf(f, "%d %d %d ", to_int(rendered[i].x), to_int(rendered[i].y), to_int(rendered[i].z));
    }
}