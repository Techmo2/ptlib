#include "ptl_material.h"

struct Material material_init(){
    struct Material m;
    m.type = NONE;
    m.p1 = 0;
    m.p2 = 0;
    m.p3 = 0;
    m.p4 = 0;

    return m;
}