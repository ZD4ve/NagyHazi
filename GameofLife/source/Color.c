#include "../include/Color.h"

Color_theme Cinit() {
    //A program indítasa utan mindig uyganazt a szint adja vissza;
    static int PrimHue = -1;
    if(PrimHue == -1){
        srand(time(NULL));
        PrimHue = rand();
    }

    Color_theme new;
    new.prim    = (SDL_Color){255, 255, 255, 0};
    new.primacc = (SDL_Color){200, 200, 200, 0};
    new.sec     = (SDL_Color){  0,   0,   0, 0};
    new.secacc  = (SDL_Color){ 55,  55,  55, 0};
    return new;
}