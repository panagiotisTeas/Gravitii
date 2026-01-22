#ifndef _GRAVITII_ARENA_H
#define _GRAVITII_ARENA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (sizeof(void*))
#endif // DEFAULT_ALIGNMENT

typedef struct
{
    u64 size;
    u64 offset;
} Arena;

Arena*  arenaCreate(u64 size);
void    arenaDestroy(Arena* arena);
void    arenaFree(Arena* arena);

void*   _arenaAllocate(Arena* arena, u64 size);

#define arenaPush(arena, type)              (type*)_arenaAllocate((arena), sizeof(type))
#define arenaPushArray(arena, type, count)  (type*)_arenaAllocate((arena), sizeof(type) * (count))
#define arenaPushStruct(arena, type)        (type*)_arenaAllocate((arena), sizeof(type))

char* arenaPushString(Arena* arena, const char* string);

u64     arenaGetPos(Arena* arena);
void    arenaSetPos(Arena* arena, u64 position);

#ifdef __cplusplus
}
#endif

#endif // _GRAVITII_ARENA_H