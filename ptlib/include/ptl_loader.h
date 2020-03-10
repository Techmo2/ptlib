#ifndef PTLIB_LOADER_h
#define PTLIB_LOADER_h

#include "ptl_list.h"
#include "ptl_config.h"
#include "ptl_sphere.h"
#include "ptl_scene.h"

#include <stdio.h>
#include <string.h>

int load_pt_scene_file(char* path, struct Scene* scene);

#endif // PTLIB_LOADER_h
