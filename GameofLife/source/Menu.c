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
        menu->saves[i].location = (SDL_Rect){30, 150 + i * (h + 10), w, h};
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

Menu Minit() {
    Menu menu;
    menu.G = Gnew("Game of Life by David Zoller", 500, 800, false);
    menu.saves = (Fgame_file *)malloc(max_saves * sizeof(Fgame_file));
    menu.save_cnt = Flist(menu.saves, max_saves);
    menu.game_open.G.win = NULL;
    draw(&menu);
    return menu;
}

void Mclose(Menu *menu) {
    Wclose(&menu->game_open);
    for (size_t i = 0; i < menu->save_cnt; i++) {
        free(menu->saves[i].path);
    }
    free(menu->saves);
    Gclose(&menu->G);
}
void Mclick(Menu *menu, int x, int y) {
    SDL_Point click = {x, y};
    for (size_t i = 0; i < menu->save_cnt; i++) {
        if (SDL_PointInRect(&click, &menu->saves[i].location)) {
            Wclose(&menu->game_open);
            menu->game_open = Winit(Fopen(menu->saves[i].path), menu->saves[i].path);
        }
    }
}
void Mevent(Menu *menu, SDL_Event e) {
    static bool mouse_down = false;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    switch (e.type) {
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                Mclose(menu);
                Gquit();
                exit(0);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (mouse_down) break;
            mouse_down = true;
            Mclick(menu, mouse_x, mouse_y);
            break;
        case SDL_MOUSEBUTTONUP:
            mouse_down = false;
            break;
    }
}
