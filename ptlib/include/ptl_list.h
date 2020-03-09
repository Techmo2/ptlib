#ifndef PTLIB_LIST_h
#define PTLIB_LIST_h

#include <stdlib.h>

typedef struct _BaseList
{
    void *buffer;
    size_t   index;
    size_t   length;
    size_t   capacity;
} BaseList;

#define List(type)         \
    struct                  \
    {                       \
        type *buffer;       \
        size_t   element_size; \
        size_t   index;        \
        size_t   length;       \
        size_t   capacity;     \
    } *

BaseList *list_new_  (size_t elem_size);
void      list_delete(BaseList *list);
void      list_resize(BaseList *list, size_t new_size);

#define list_new(type) (List (type) ) list_new_(sizeof(type));

#define list_push(list, data)    \
    if(list->index > list->length) \
        list_resize(list, list->capacity * 2); \
    list->buffer[list->index++] = data;        \
    list->length++;

#endif // PTL_LIST_h