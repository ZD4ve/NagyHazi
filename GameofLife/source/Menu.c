#include "../include/Menu.h"


static void Mdrawtitle(Gwindow window){
    (void)window;
}
static void Mdraw_background(Gwindow window){
    (void)window;
}

Gwindow Minit(){
    Gwindow window = Gnew("Game Of Life by Zoller David",500,800);
    Mdraw_background(window);
    Mdrawtitle(window);
    return window;
}
