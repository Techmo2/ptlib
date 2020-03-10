#ifndef PTLIB_CONFIG_h
#define PTLIB_CONFIG_h

#include <stdint.h>


/* Modify Here */

//#define USE_SINGLE_PRECISION

#define MAX_TRACE_DEPTH 5

#define PI 3.14159265

#define COMMENT_CHAR '#'

#define PTS_WHITESPACE " \t"

/* ------------- */



#ifdef USE_SINGLE_PRECISION

#define PRECISION "single"
#define EPS 1e-2
#define INF FLT_MAX
#define PTNUM float

#else

#define PRECISION "double"
#define EPS 1e-4
#define INF DBL_MAX
#define PTNUM double

#endif

#ifndef MAKE_OPENMP_OVERRIDE
#define ENABLE_OPENMP
#endif

#endif //PTLIB_CONFIG_h