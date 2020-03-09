#include "ptl_util.h"
#include "ptl_config.h"
#include "ptl_sphere.h"

#include <stdio.h>
#include <string.h>

PTNUM clamp(PTNUM x)
{
    if (x < 0)
    {
        return 0;
    }

    if (x > 1)
    {
        return 1;
    }

    return x;
}

int to_int(PTNUM x)
{
    return (int)(pow(clamp(x), 0.454545) * 255 + 0.5);
}

int intersects(struct Ray *r, PTNUM *t, int *id, struct TraceableList *list)
{
    PTNUM d;
    PTNUM inf = INF;
    PTNUM eps = EPS;
    PTNUM n = list->size;
    struct Traceable *items = list->elements;

    *t = inf;

    for (int i = list->size; i--;)
    {
        struct Traceable current = items[i];
        //fprintf(stdout, "CURRENT: %f %f %f\n", current.position.x, current.position.y, current.position.z);
        d = items[i].intersect(r, &current);

        if (d > eps && d < *t)
        {
            *t = d;
            *id = i;
            //fprintf(stdout, "GOT ONE: T: %f   ID: %d\n", *t, *id);
        }
    }

    //fprintf(stdout, "RESULT: %d\n", *t < inf);
    return *t < inf;
}

int load_pt_scene_file(char *path, struct Scene *scene)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    int n_lines = 0;

    fp = fopen(path, "r");

    if (fp == NULL)
        return -1;

    // Iterate over lines
    while ((read = getline(&line, &len, fp)) != -1)
    {

        List (char*) tokens = list_new(char*);

        int idx = 0;
        char *pch;
        pch = strtok(line, " ,");
        while (pch != NULL)
        {
            // Copy tokens
            char* cpy = (char*) malloc(sizeof(char) * strlen(pch) + 1);
            strcpy(cpy, pch);

            list_push(tokens, cpy);

            pch = strtok(NULL, " ,");
            idx++;
        }

        if (tokens->length > 0)
        {
            // Process tokens for line
            char obj_type = tokens->buffer[0][0];

            // Only spheres supported, sorry m8
            if (obj_type == 'S')
            {
                if (tokens->length >= 12)
                {
                    PTNUM radius = atof(tokens->buffer[1]);

                    PTNUM pos_x = atof(tokens->buffer[2]);
                    PTNUM pos_y = atof(tokens->buffer[3]);
                    PTNUM pos_z = atof(tokens->buffer[4]);

                    PTNUM emission_r = atof(tokens->buffer[5]);
                    PTNUM emission_g = atof(tokens->buffer[6]);
                    PTNUM emission_b = atof(tokens->buffer[7]);

                    PTNUM color_r = atof(tokens->buffer[8]);
                    PTNUM color_g = atof(tokens->buffer[9]);
                    PTNUM color_b = atof(tokens->buffer[10]);

                    char material = tokens->buffer[11][0];
                    struct Material mat = material_init();

                    if (material == 'D')
                    {
                        mat.type = PTMAT_DIFFUSE;
                    }
                    else if (material == 'S')
                    {
                        mat.type = PTMAT_SPECULAR;
                    }
                    else if (material == 'R')
                    {
                        mat.type = PTMAT_REFRACT;
                    }
                    else
                    {
                        mat.type = PTMAT_DIFFUSE;
                    }

                    traceable_list_push(sphere_init(radius, vec_init(pos_x, pos_y, pos_z), vec_init(emission_r, emission_g, emission_b), vec_init(color_r, color_g, color_b), mat), scene->items);
                }
            }
        }

        // Free list
        list_delete(tokens);
        n_lines++;
    }

    fclose(fp);
    if (line)
        free(line);

    return n_lines;
}