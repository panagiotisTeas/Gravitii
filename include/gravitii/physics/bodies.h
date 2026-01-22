#ifndef _GRAVITII_BODIES_H
#define _GRAVITII_BODIES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"
#include "utils/arena.h"

#ifdef USE_SIMD

// SIMD -> SoA (Structure of Arrays)

typedef struct Bodies
{
    double* mass;
    double* x;
    double* y;
    double* vx;
    double* vy;
    u64     num_bodies;
} Bodies;

#else

// AoS (Array of Structures)

typedef struct Body
{
    double mass;
    double x;
    double y;
    double vx;
    double vy;
} Body;

typedef struct Bodies
{
    Body*   bodies;
    u64     num_bodies;
} Bodies;

#endif


Bodies* bodiesInit(const double* data, u64 num_bodies, Arena* arena);

#ifdef __cplusplus
}
#endif

#endif // _GRAVITII_BODIES_H