#include "ptl_scene.h"
#include "ptl_sphere.h"


int main(int argc, char** argv){
    int width = 1024;
    int height = 768;
    int samples = 8;

    struct Scene* scene = scene_new(800, 600, PTLIB_CPU);

    struct Material diffuse = material_init();
    diffuse.type = PTMAT_DIFFUSE;
    
    struct Material specular = material_init();
    specular.type = PTMAT_SPECULAR;

    tracable_list_push(sphere_init(1e5, vec_init(1e5 + 1, 40.8, 81.6), vec_init_e(), vec_init(0.75, 0.25, 0.25), diffuse), scene->items);

    struct Ray camera = ray_init(vec_init(50, 52, 295.6), vec_norm(vec_init(0, -0.042612, -1)));

    struct Image* rendered = scene_render_from(scene, &camera, samples, width, height);
}