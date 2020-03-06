#include "ptl_scene.h"
#include "ptl_sphere.h"
#include "ptl_util.h"
#include <stdio.h>


int main(int argc, char** argv){
    int width = 1024;
    int height = 768;
    int samples = 8;

    struct Scene* scene = scene_new(width, height, PTLIB_CPU);

    struct Material diffuse = material_init();
    diffuse.type = PTMAT_DIFFUSE;
    
    struct Material specular = material_init();
    specular.type = PTMAT_SPECULAR;

    traceable_list_push(sphere_init(1e5, vec_init(50, 1e5, 81.6),   vec_init_e() ,vec_init(.75,.75,.75),diffuse), scene->items);
    traceable_list_push(sphere_init(1e5, vec_init(1e5 + 1, 40.8, 81.6), vec_init_e(), vec_init(0.75, 0.25, 0.25), diffuse), scene->items);
    traceable_list_push(sphere_init(600, vec_init(50,681.6-.27,81.6), vec_init(1, 12, 1), vec_init_e(), diffuse), scene->items);

    struct Ray camera = ray_init(vec_init(50, 52, 295.6), vec_norm(vec_init(0, -0.042612, -1)));

    struct Vec* rendered = scene_render_from(scene, camera, samples, width, height);
    
    FILE *f = fopen("output.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);

    for(int i = 0; i < width * height; i++){
        fprintf(f, "%d %d %d ", to_int(rendered[i].x), to_int(rendered[i].y), to_int(rendered[i].z));
    }
}