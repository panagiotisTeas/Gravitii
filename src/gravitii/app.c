#include "physics/bodies.h"
#include "utils/arena.h"
#include "app.h"

#include "raylib.h"

#define WIDTH   800
#define HEIGHT  600
#define TITLE   "Gravitii"
#define FPS     60

const double DEFAULT_BODY_INIT_DATA[] = {1.0, 0.0, 0.0, 0.0, 0.0,
                                         1.0, 1.0, 2.0, 3.0, 1.0,
                                         1.0, 4.0, 1.0, 2.0, 1.0};
#define NUM_BODIES 3

Arena* g_arena = {0};
Bodies* g_bodies = {0};

void gravitiiInitConfig(Gravitii* config)
{
    assert(!(config == NULL));
    config->body_init_data = DEFAULT_BODY_INIT_DATA;
    config->num_bodies = NUM_BODIES;

    config->window_width = WIDTH;
    config->window_height = HEIGHT;
    config->window_title = TITLE;
    config->window_fps = FPS;
}

static void init(Gravitii* config)
{
    assert(!(config == NULL));

    g_arena = arenaCreate(MiB(4));
    g_bodies = bodiesInit(config->body_init_data, config->num_bodies, g_arena);

    InitWindow(config->window_width, config->window_height, config->window_title);
    SetTargetFPS(config->window_fps);
}

static void update()
{

}

static void draw()
{
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    }
    EndDrawing();
}

static void terminate()
{
    CloseWindow();

    arenaDestroy(g_arena);
    g_arena = NULL;
}

void gravitiiRun(Gravitii* config)
{
    assert(!(config == NULL));

    init(config);
    while (!WindowShouldClose())
    {
        update();
        draw();
    }
    terminate();
}