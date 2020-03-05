#include "ptl_util.h"

inline PTNUM clamp(PTNUM x){
    if(x < 0) {
        return 0;
    }
    
    if(x > 1){
        return 1;
    }

    return x;
}

inline int to_int(PTNUM x){
    return (int) (pow(clamp(x), 0.454545) * 255 + 0.5);
}

inline int intersects(struct Ray *r, PTNUM *t, int *id, struct TraceableList *list){
    PTNUM d;
    PTNUM inf;
    PTNUM n = list->size;
    struct Traceable* items = list->elements;

    #if PTNUM == float
        inf = FLT_MAX;
    #endif

    #if PTNUM == double
        inf = DBL_MAX;
    #endif

    *t = inf;

    PTNUM eps = 1e-4;

    for(int i = (int) (n); i--;){
        d = items[i].intersect(r, &(items[i]));

        if(d > eps && d < *t){
            *t = d;
            *id = i;
        }
    }

    return *t < inf;
}