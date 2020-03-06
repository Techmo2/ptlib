#ifndef PTLIB_TEST_DYNARR_h
#define PTLIB_TEST_DYNARR_h

#include <stdlib.h>
#include <string.h>

struct dynarr {
    size_t capacity;
    size_t size;
    char** strs;
};

struct dynarr* dynarr_new(size_t capacity_);
void dynarr_add(struct dynarr* arr, char* s);
void dynarr_set(struct dynarr* arr, size_t idx, char* s);
char* dynarr_get(struct dynarr* arr, size_t idx);
void dynarr_free(struct dynarr* arr);

#endif //PTLIB_TEST_DYNARR_h