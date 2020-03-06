#include "ptl_scene.h"
#include "ptl_sphere.h"
#include "ptl_util.h"
#include "dynarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int load_pt_scene_file(char* path, struct Scene* scene){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int n_lines = 0;

    fp = fopen(path, "r");

    if(fp == NULL)
        return -1;

    // Iterate over lines
    while((read = getline(&line, &len, fp)) != -1){

        struct dynarr* tokens = dynarr_new(10);

        int idx = 0;
        char *pch;
        pch = strtok(line, " ,");
        while(pch != NULL){
            dynarr_add(tokens, pch);

            pch = strtok(NULL, " ,");
            idx++;
        }

        if(tokens->size > 0){
        // Process tokens for line
        char* obj_type = tokens->strs[0];

        // Only spheres supported, sorry m8
        if(obj_type[0] == 'S'){
            if(tokens->size >= 12){
                PTNUM radius = atof(dynarr_get(tokens, 1));

                PTNUM pos_x = atof(dynarr_get(tokens, 2));
                PTNUM pos_y = atof(dynarr_get(tokens, 3));
                PTNUM pos_z = atof(dynarr_get(tokens, 4));

                PTNUM emission_r = atof(dynarr_get(tokens, 5));
                PTNUM emission_g = atof(dynarr_get(tokens, 6));
                PTNUM emission_b = atof(dynarr_get(tokens, 7));

                PTNUM color_r = atof(dynarr_get(tokens, 8));
                PTNUM color_g = atof(dynarr_get(tokens, 9));
                PTNUM color_b = atof(dynarr_get(tokens, 10));

                char material = dynarr_get(tokens, 11)[0];
                struct Material mat = material_init();

                if(material == 'D'){
                    mat.type = PTMAT_DIFFUSE;
                }
                else if(material == 'S'){
                    mat.type = PTMAT_SPECULAR;
                }
                else if(material == 'R'){
                    mat.type = PTMAT_REFRACT;
                }
                else{
                    mat.type = PTMAT_DIFFUSE;
                }

                traceable_list_push(sphere_init(radius, vec_init(pos_x, pos_y, pos_z), vec_init(emission_r, emission_g, emission_b), vec_init(color_r, color_g, color_b), mat), scene->items);
            }
        }
        }
        dynarr_free(tokens);
        n_lines++;
    }

    fclose(fp);
    if(line)
        free(line);

    return n_lines;
}

int main(int argc, char** argv){
    int width = 1024;
    int height = 768;
    int samples = 8;

    struct Scene* scene = scene_new(width, height, PTLIB_CPU);

    load_pt_scene_file("example.pts", scene);

    /*
    struct Material diffuse = material_init();
    diffuse.type = PTMAT_DIFFUSE;
    
    struct Material specular = material_init();
    specular.type = PTMAT_SPECULAR;

    traceable_list_push(sphere_init(1e5, vec_init(50, 1e5, 81.6),   vec_init_e() ,vec_init(.75,.75,.75),diffuse), scene->items);
    traceable_list_push(sphere_init(1e5, vec_init(1e5 + 1, 40.8, 81.6), vec_init_e(), vec_init(0.75, 0.25, 0.25), diffuse), scene->items);
    traceable_list_push(sphere_init(600, vec_init(50,681.6-.27,81.6), vec_init(1, 12, 1), vec_init_e(), diffuse), scene->items);
    */

    struct Ray camera = ray_init(vec_init(50, 52, 295.6), vec_norm(vec_init(0, -0.042612, -1)));

    struct Vec* rendered = scene_render_from(scene, camera, samples, width, height);
    
    FILE *f = fopen("output.ppm", "w");
    fprintf(f, "P3\n%d %d\n%d\n", width, height, 255);

    for(int i = 0; i < width * height; i++){
        fprintf(f, "%d %d %d ", to_int(rendered[i].x), to_int(rendered[i].y), to_int(rendered[i].z));
    }
}