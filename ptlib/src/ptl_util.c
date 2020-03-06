#include "ptl_util.h"
#include "ptl_config.h"

#include <stdio.h>

PTNUM clamp(PTNUM x){
    if(x < 0) {
        return 0;
    }
    
    if(x > 1){
        return 1;
    }

    return x;
}

int to_int(PTNUM x){
    return (int) (pow(clamp(x), 0.454545) * 255 + 0.5);
}

int intersects(struct Ray *r, PTNUM *t, int *id, struct TraceableList *list){
    PTNUM d;
    PTNUM inf = INF;
    PTNUM eps = EPS;
    PTNUM n = list->size;
    struct Traceable* items = list->elements;

    *t = inf;

    for(int i = list->size; i--;){
        struct Traceable current = items[i];
        //fprintf(stdout, "CURRENT: %f %f %f\n", current.position.x, current.position.y, current.position.z);
        d = items[i].intersect(r, &current);

        if(d > eps && d < *t){
            *t = d;
            *id = i;
          //fprintf(stdout, "GOT ONE: T: %f   ID: %d\n", *t, *id);
        }
    }

    //fprintf(stdout, "RESULT: %d\n", *t < inf);
    return *t < inf;
}