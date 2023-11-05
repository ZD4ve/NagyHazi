#include "../include/Menu.h"

static void draw_title(Gwindow window) {
    Gprint_title(window);
}
static void draw_background(Gwindow window) {
    Gfill_background(window);
}

static void print_file_names(Menu M) {
    const int
        w = 200,
        h = 40;
    for (size_t i = 0; i < M.save_cnt; i++) {
        M.saves[i].location = (SDL_Rect){30, 150 + i * (h+10), w, h};
        SDL_Rect text_loc = Grectwithborders(M.G, M.saves[i].location, 5, primary);
        Gprint(M.G, M.saves[i].path, text_loc, secondary);
    }
}

static void Mdrawbase(Gwindow window) {
    draw_background(window);
    draw_title(window);
    SDL_RenderPresent(window.ren);
}

static bool is_in_rect(int x, int y, SDL_Rect r){
    if(x<r.x) return false;
    if(y<r.y) return false;
    if(r.x+r.w<x) return false;
    if(r.y+r.h<y) return false;
    return true;
} 

Menu Minit() {
    Menu M;
    M.G = Gnew("Game Of Life by Zoller David", 500, 800);
    M.saves = (Fgame_file*)malloc(max_saves*sizeof(Fgame_file));
    M.save_cnt = Flist(M.saves, max_saves);
    Mdrawbase(M.G);
    print_file_names(M);
    return M;
}
void Mclose(Menu menu){
    for (size_t i = 0; i < menu.save_cnt; i++)
    {
        free(menu.saves[i].path);
    }
    free(menu.saves);
    Gclose(menu.G);
}
void Mclick(Menu menu, int x, int y){
    for (size_t i = 0; i < menu.save_cnt; i++)
    {
        if(is_in_rect(x,y,menu.saves[i].location)){
            //benne van :)
        }
    }
    
}
