/*

Author: Bradly Tillmann

A simple vector with various vector operations.

*/

#ifndef PTLIB_VECTOR_h
#define PTLIB_VECTOR_h

#include "ptl_config.h"

/* Ensure the sqrt() function is available of not using OpenCL */
#ifndef __OPENCL_VERSION__
#include <math.h>
#endif

struct Vec {
  union {
    struct {
      PTNUM x, y, z;
    };

    struct {
      PTNUM r, g, b;
    };
  };
};

struct Vec vec_init_e();

struct Vec vec_init(PTNUM x_, PTNUM y_, PTNUM z_);

struct Vec vec_add(struct Vec a, struct Vec b);

struct Vec vec_sub(struct Vec a, struct Vec b);

struct Vec vec_mult(struct Vec a, PTNUM b);

struct Vec vec_multv(struct Vec a, struct Vec b);

struct Vec vec_norm(struct Vec a);

PTNUM vec_dot(struct Vec a, struct Vec b);

struct Vec vec_cross(struct Vec a, struct Vec b);

struct Vec vec_div(struct Vec a, PTNUM b);

#endif //PTLIB_VECTOR_h