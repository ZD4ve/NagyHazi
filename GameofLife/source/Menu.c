#include "../include/Menu.h"

static void draw_title(Gwindow window) {
    Gprint_title(window);
}
static void draw_background(Gwindow window) {
    Gfill_background(window);
}

static void print_file_names(Gwindow window, Fgame_file files[], size_t cnt) {
    const int
        w = 200,
        h = 40;
    for (size_t i = 0; i < cnt; i++) {
        files[i].location = (SDL_Rect){30, 150 + i * (h+10), w, h};
        SDL_Rect text_loc = Grectwithborders(window, files[i].location, 5, primary);
        Gprint(window, files[i].path, text_loc, secondary);
    }
}

static void Mdrawbase(Gwindow window) {
    draw_background(window);
    draw_title(window);
    SDL_RenderPresent(window.ren);
}
void Mfree_files(Fgame_file saves[], size_t cnt){
    for (size_t i = 0; i < cnt; i++)
    {
        free(saves[i].path);
    }
    
}

Gwindow Minit() {
    Gwindow window = Gnew("Game Of Life by Zoller David", 500, 800);
    Fgame_file saves[10];
    size_t cnt = Flist(saves, 10);
    Mdrawbase(window);
    print_file_names(window, saves, cnt);
    Mfree_files(saves,cnt);
    return window;
}
