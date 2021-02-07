#ifndef PTLIB_MATERIAL_h
#define PTLIB_MATERIAL_h

// #define MATERIAL_NAME_LENGTH 20

enum PTMAT {
    PTMAT_DIFFUSE,
    PTMAT_SPECULAR,
    PTMAT_REFRACT,
    NONE
};

struct Material {
    enum PTMAT type;
    union {
        struct {
            float properties[4];
        };

        struct {
            float p1;
            float p2;
            float p3;
            float p4;
        };
    };
};

static inline struct Material material_init(){
    struct Material m;
    m.type = NONE;
    m.p1 = 0;
    m.p2 = 0;
    m.p3 = 0;
    m.p4 = 0;

    return m;
}

#endif //PTLIB_MATERIAL_h