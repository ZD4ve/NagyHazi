#include "../include/Menu.h"

static void draw_title(Gwindow *window) {
    Gprint_title(window);
}
static void draw_background(Gwindow *window) {
    Gfill_background(window);
}

static void print_file_names(Menu *menu) {
    const int
        w = 200,
        h = 40;
    for (size_t i = 0; i < menu->save_cnt; i++) {
        menu->saves[i].location = (SDL_Rect){30, 150 + i * (h+10), w, h};
        SDL_Rect text_loc = Grectwithborders(&menu->G, menu->saves[i].location, 5, primary);
        Gprint(&menu->G, menu->saves[i].path, &text_loc, secondary);
    }
}

static void draw(Menu *menu) {
    draw_background(&menu->G);
    draw_title(&menu->G);
    print_file_names(menu);
    SDL_RenderPresent(menu->G.ren);
}

static bool is_in_rect(int x, int y, SDL_Rect r){
    if(x<r.x) return false;
    if(y<r.y) return false;
    if(r.x+r.w<x) return false;
    if(r.y+r.h<y) return false;
    return true;
} 

Menu Minit() {
    Menu menu;
    menu.G = Gnew("Game Of Life by Zoller David", 500, 800,false);
    menu.saves = (Fgame_file*)malloc(max_saves*sizeof(Fgame_file));
    menu.save_cnt = Flist(menu.saves, max_saves);
    draw(&menu);
    return menu;
}

void Mclose(Menu *menu){
    for (size_t i = 0; i < menu->save_cnt; i++)
    {
        free(menu->saves[i].path);
    }
    free(menu->saves);
    Gclose(&menu->G);
}
void Mclick(Menu *menu, int x, int y){
    for (size_t i = 0; i < menu->save_cnt; i++)
    {
        if(is_in_rect(x,y,menu->saves[i].location)){
            //benne van :)
        }
    }
    
}
