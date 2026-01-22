#ifndef _GRAVITII_APP_H
#define _GRAVITII_APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

typedef struct Gravitii 
{
    // bodies data (assume that the user will pass the correct combination of body_init_data count and num_bodies)
    const double*   body_init_data;
    u64             num_bodies;

    // window
    const char* window_title;
    u16         window_width;
    u16         window_height;
    u16         window_fps;
} Gravitii;

void gravitiiInitConfig(Gravitii* config);
void gravitiiRun(Gravitii* config);

#ifdef __cplusplus
}
#endif

#endif // _GRAVITII_APP_H