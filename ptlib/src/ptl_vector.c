#include "ptl_vector.h"

#include <stdio.h>


struct Vec vec_init_e(){
  struct Vec v;

  v.x = 0;
  v.y = 0;
  v.z = 0;

  return v;
}

struct Vec vec_init(PTNUM x_, PTNUM y_, PTNUM z_){
  struct Vec v;
  v.x = x_;
  v.y = y_;
  v.z = z_;

  return v;
}

struct Vec vec_add(struct Vec a, struct Vec b) { 
    struct Vec v;
    v.x = a.x + b.x;
    v.y = a.y + b.y;
    v.z = a.z + b.z;
    return v;
}

struct Vec vec_sub(struct Vec a, struct Vec b){
    struct Vec v;
    v.x = a.x - b.x;
    v.y = a.y - b.y;
    v.z = a.z - b.z;
    return v;
}

struct Vec vec_mult(struct Vec a, PTNUM b){
    struct Vec v;
    v.x = a.x * b;
    v.y = a.y * b;
    v.z = a.z * b;
    return v;
}

struct Vec vec_multv(struct Vec a, struct Vec b){
    struct Vec v;
    v.x = a.x * b.x;
    v.y = a.y * b.y;
    v.z = a.z * b.z;
    return v;
}

struct Vec vec_norm(struct Vec a){
  return vec_mult(a, (PTNUM) (1/sqrt(a.x*a.x+a.y*a.y+a.z*a.z)));
}

PTNUM vec_dot(struct Vec a, struct Vec b) {
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

struct Vec vec_cross(struct Vec a, struct Vec b){
  struct Vec v;

  v.x = a.y*b.z-a.z*b.y;
  v.y = a.z*b.x-a.x*b.z;
  v.z = a.x*b.y-a.y*b.x;

  return v;
}

struct Vec vec_div(struct Vec a, PTNUM b){
  struct Vec v;


  PTNUM inv = ((PTNUM) 1.0) / b;

  v.x = a.x * inv;
  v.y = a.y * inv;
  v.z = a.z * inv;


  return v;
}