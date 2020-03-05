#include "ptl_traceable_list.h"
#include <stdlib.h>

struct TraceableList* traceable_list_new(unsigned int capacity_){
    struct TraceableList *list;

    list = (struct TraceableList*) malloc(sizeof(struct TraceableList));

    list->capacity = capacity_;
    list->size = 0;
    list->elements = (struct Traceable*) malloc(sizeof(struct Traceable) * capacity_);

    return list;
}

void traceable_list_grow(struct TraceableList *list){
    list->capacity = list->capacity * 2;
    list->elements = (struct Traceable*) realloc(list->elements, sizeof(struct Traceable) * list->capacity);
}

void traceable_list_push(struct Traceable t, struct TraceableList *list){
    if(list->size >= list->capacity){
        tracable_list_grow(list);
    }

    list->elements[list->size] = t;
    list->size = list->size + 1;
}

void traceable_list_free(struct TraceableList *list){
    free(list->elements);
    free(list);
}