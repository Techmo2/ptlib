#include "ptl_loader.h"

static void cleanstr(char* input, char* output){
    int c = 0, d = 0;


    while (input[c] != '\0') {
      if (input[c] == ' ') {
         int temp = c + 1;
         if (input[temp] != '\0') {
            while (input[temp] == ' ' && input[temp] != '\0') {
               if (input[temp] == ' ') {
                  c++;
               }  
               temp++;
            }
         }
      }
      output[d] = input[c];
      c++;
      d++;
   }

   output[d] = '\0';
}

int load_pt_scene_file(char *path, struct Scene *scene)
{
    FILE *fp;
    char *line = NULL;
    char *clean = NULL;
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

        // clean line
        char* clean = (char*) malloc(sizeof(char) * strlen(line) + 1);
        cleanstr(line, clean);

        pch = strtok(clean, PTS_WHITESPACE);

        while (pch != NULL)
        {
            char* cpy = (char*) malloc(sizeof(char) * strlen(pch) + 1);
            strcpy(cpy, pch);

            // Be sure to cut off at any comments
            // Cut the token if necessary
            char* cmt_ptr;
            int cmt_found = 0;
            cmt_ptr = strchr(cpy, COMMENT_CHAR);;
            if(cmt_ptr != NULL){
                *cmt_ptr = '\0';
                cmt_found = 1;
            }


            char* fin = (char*) malloc(sizeof(char) * strlen(pch) + 1);
            strcpy(fin, pch);
            char* tmp = cpy;
            cpy = fin;
            free(tmp);

            if(cpy && strlen(cpy) >= 1){
                if(cpy[0] != ' ') {
                    list_push(tokens, cpy);
                }
            }

            // Done parsing line if there was a comment
            if(cmt_found == 1)
                break;

            pch = strtok(NULL, PTS_WHITESPACE);
            idx++;
        }

        if (tokens->length > 0)
        {
            if (strcmp(tokens->buffer[0], "SPHERE") == 0)
            {
                if (tokens->length >= 12)
                {
                    PTNUM pos_x = atof(tokens->buffer[1]);
                    PTNUM pos_y = atof(tokens->buffer[2]);
                    PTNUM pos_z = atof(tokens->buffer[3]);

                    PTNUM emission_r = atof(tokens->buffer[4]);
                    PTNUM emission_g = atof(tokens->buffer[5]);
                    PTNUM emission_b = atof(tokens->buffer[6]);

                    PTNUM color_r = atof(tokens->buffer[7]);
                    PTNUM color_g = atof(tokens->buffer[8]);
                    PTNUM color_b = atof(tokens->buffer[9]);

                    char* material = tokens->buffer[10];
                    struct Material mat = material_init();

                    PTNUM radius = atof(tokens->buffer[11]);

                    if (strcmp(material, "MAT_DIFFUSE") == 0)
                    {
                        mat.type = PTMAT_DIFFUSE;
                    }
                    else if (strcmp(material, "MAT_SPECULAR") == 0)
                    {   
                        mat.type = PTMAT_SPECULAR;
                    }
                    else if (strcmp(material, "MAT_REFRACT") == 0)
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

    if (clean)
        free(clean);

    return n_lines;
}