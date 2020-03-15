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

struct Material material_init();

#endif //PTLIB_MATERIAL_h