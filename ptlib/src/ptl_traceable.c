#include "ptl_traceable.h"

struct Traceable traceable_init(struct Properties properties_, struct Vec position_, struct Vec emission_, struct Vec color_, struct Material material_, PTNUM (*intersect_)(struct Ray *r, struct Traceable *tb)){
    struct Traceable t;
    t.properties = properties_;
    t.position = position_;
    t.emission = emission_;
    t.color = color_;
    t.material = material_;
    t.intersect = intersect_;

    return t;
}

struct Traceable traceable_init_e(){
    struct Traceable t;
    struct Properties p;

    t.properties = p;
    t.position = vec_init_e();
    t.emission = vec_init_e();
    t.color = vec_init_e();
    t.material = material_init();

    t.intersect = 0;

    return t;
}