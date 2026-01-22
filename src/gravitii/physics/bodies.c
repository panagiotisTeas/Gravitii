#include "physics/bodies.h"

#include "raylib.h"

Bodies* bodiesCreate(const double* data, u64 num_bodies, Arena* arena)
{
    assert(!(arena == NULL));
    assert(!(data == NULL));

    Bodies* bodies = arenaPushStruct(arena, Bodies);

    #ifdef USE_SIMD

    bodies->num_bodies = num_bodies;
    bodies->mass = arenaPushArray(arena, double, num_bodies);
    bodies->x = arenaPushArray(arena, double, num_bodies);
    bodies->y = arenaPushArray(arena, double, num_bodies);
    bodies->vx = arenaPushArray(arena, double, num_bodies);
    bodies->vy = arenaPushArray(arena, double, num_bodies);

    for (u64 i = 0; i < num_bodies; ++i)
    {
        u64 offset = 5 * i;
        bodies->mass[i] = data[offset + 0];
        bodies->x[i] = data[offset + 1];
        bodies->y[i] = data[offset + 2];
        bodies->vx[i] = data[offset + 3];
        bodies->vy[i] = data[offset + 4];
    }

    #else

    bodies->num_bodies = num_bodies;
    bodies->bodies = arenaPushArray(arena, Body, num_bodies);

    for (u64 i = 0; i < num_bodies; ++i)
    {
        u64 offset = 5 * i;
        bodies->bodies[i].mass = data[offset + 0];
        bodies->bodies[i].x = data[offset + 1];
        bodies->bodies[i].y = data[offset + 2];
        bodies->bodies[i].vx = data[offset + 3];
        bodies->bodies[i].vy = data[offset + 4];
    }

    #endif

    return bodies;
}

void bodiesDraw(Bodies* bodies)
{
    #ifdef USE_SIMD

    for (u64 i = 0; i < bodies->num_bodies; ++i)
    {
        DrawCircle(bodies->x[i], bodies->y[i], 3, RAYWHITE);
    }

    #else

    for (u64 i = 0; i < bodies->num_bodies; ++i)
    {
        DrawCircle(bodies->bodies[i].x, bodies->bodies[i].y, 3, RAYWHITE);
    }

    #endif
}