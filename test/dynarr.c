#include "dynarr.h"

struct dynarr* dynarr_new(size_t capacity_){
    struct dynarr* arr = (struct dynarr*) malloc(sizeof(struct dynarr));

    arr->capacity = capacity_;
    arr->size = 0;

    arr->strs = (char**) malloc(sizeof(char*) * capacity_);

    return arr;
}

void dynarr_add(struct dynarr* arr, char* s){
    if(arr->size >= arr->capacity){

        arr->capacity = arr->capacity * 2;
        char** strs_new = (char**) malloc(sizeof(char*) * arr->capacity);

        for(int idx = 0; idx < arr->size; idx++){
            strs_new[idx] = arr->strs[idx];
        }

        free(arr->strs);
        arr->strs = strs_new;
    }

    arr->strs[arr->size] = (char*) malloc(sizeof(char) * (strlen(s) + 1));
    memcpy(arr->strs[arr->size], s, strlen(s) + 1);
    arr->size = arr->size + 1;
}

void dynarr_set(struct dynarr* arr, size_t idx, char* s){
    if(idx < arr->size){
        free(arr->strs[idx]);

        arr->strs[idx] = (char*) malloc(sizeof(char) * (strlen(s) + 1));
        memcpy(arr->strs[idx], s, strlen(s) + 1);
    }
}

char* dynarr_get(struct dynarr* arr, size_t idx){
    if(idx < arr->size){
        return arr->strs[idx];
    }
    return NULL;
}

void dynarr_free(struct dynarr* arr){
    free(arr->strs);
    free(arr);
}
