#include "../include/Menu.h"


static void draw_title(Gwindow window){
    Gprint_title(window);
}
static void draw_background(Gwindow window){
    Gfill_background(window);
}
void Mdraw(Gwindow window){
    draw_background(window);
    draw_title(window);
    //TEST
    SDL_Rect hova1 = {100,200,100,30};
    Grectwithborders(window,hova1,5,primary);

    SDL_Rect hova2 = {100,250,100,30};
    Grectwithborders(window,hova2,5,secondary);
    //END TEST
    SDL_RenderPresent(window.ren);
}
Gwindow Minit(){
    Gwindow window = Gnew("Game Of Life by Zoller David",500,800);
    Mdraw(window);
    return window;
}
