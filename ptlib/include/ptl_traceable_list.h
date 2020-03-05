#ifndef TRACABLE_LIST_h
#define TRACABLE_LIST_h

#include "ptl_traceable.h"

struct TraceableList {
    unsigned int size;
    unsigned int capacity;
    struct Traceable* elements;
};

struct TraceableList* tracable_list_new(unsigned int capacity_);

void tracable_list_grow(struct TraceableList *list);

void tracable_list_push(struct Traceable t, struct TraceableList *list);

void tracable_list_free(struct TraceableList *list);

#endif //TRACABLE_LIST_h