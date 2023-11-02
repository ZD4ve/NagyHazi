#include "../include/Menu.h"


static void Mdrawtitle(Gwindow window){
    Gprint_title(window);
}
static void Mdraw_background(Gwindow window){
    (void)window;
}
void Mdraw(Gwindow window){
    Mdraw_background(window);
    Mdrawtitle(window);
    SDL_RenderPresent(window.ren);
}
Gwindow Minit(){
    Gwindow window = Gnew("Game Of Life by Zoller David",500,800);
    Mdraw(window);
    return window;
}
