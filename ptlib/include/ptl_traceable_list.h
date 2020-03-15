#ifndef traceable_LIST_h
#define traceable_LIST_h

#include "ptl_traceable.h"

struct TraceableList {
    unsigned int size;
    unsigned int capacity;
    struct TraceableObject* elements;
};

struct TraceableList* traceable_list_new(unsigned int capacity_);

void traceable_list_grow(struct TraceableList *list);

void traceable_list_push(struct TraceableObject t, struct TraceableList *list);

void traceable_list_free(struct TraceableList *list);

#endif //traceable_LIST_h