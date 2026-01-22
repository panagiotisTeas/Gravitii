#include "utils/arena.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

Arena* arenaCreate(u64 size)
{
    Arena* arena = (Arena*)malloc(sizeof(Arena) + size);
    arena->size = size;
    arena->offset = 0;

    return arena;
}

//! Callers responsibility to nullify the pointer
void arenaDestroy(Arena* arena)
{
    assert(!(arena == NULL));

    free(arena);
}

void arenaFree(Arena* arena)
{
    assert(!(arena == NULL));

    arena->offset = 0;
}

void* _arenaAllocate(Arena* arena, u64 size)
{
    assert(!(arena == NULL));

    if (DEFAULT_ALIGNMENT == 0 || (DEFAULT_ALIGNMENT & (DEFAULT_ALIGNMENT - 1)) != 0) 
    {
        fprintf(stderr, "Alignment is not a power of 2!\n");
        return NULL;
    }

    u64 curr_offset = arena->offset;
    u64 aligned_offset = (curr_offset + DEFAULT_ALIGNMENT - 1) & ~ (DEFAULT_ALIGNMENT - 1);

    if (aligned_offset + size > arena->size)
    {
        fprintf(stderr, "Not enough space in arena!\n");
        return NULL;
    }

    void* alloc_address = (u8*)arena + sizeof(Arena) + aligned_offset;
    memset(alloc_address, 0, size);
    arena->offset = aligned_offset + size;

    return alloc_address;
}

char* arenaPushString(Arena* arena, const char* string)
{
    assert(!(arena == NULL));
    assert(!(string == NULL));

    u64 string_length = strlen(string) + 1;
    char* str = (char*)_arenaAllocate(arena, string_length);

    if (str != NULL)
        memcpy(str, string, string_length);

    return str;
}

u64 arenaGetPos(Arena* arena)
{
    assert(!(arena == NULL));

    return arena->offset;
}

void arenaSetPos(Arena* arena, u64 position)
{
    assert(!(arena == NULL));
    assert(position <= arena->size);

    arena->offset = position;
}