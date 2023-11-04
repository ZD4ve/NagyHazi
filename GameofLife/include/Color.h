#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum Colortype 
{ 
    primary, 
    secondary
} Colortype;

typedef struct Color_theme {
    SDL_Color
        prim,
        primacc,
        sec,
        secacc;
} Color_theme;

Color_theme Cinit();
#endif