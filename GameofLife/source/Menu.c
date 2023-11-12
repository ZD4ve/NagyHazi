#include "../include/Menu.h"

#define BUTTON_HEIGHT 40
#define BUTTON_WIDTH 200

static void draw_title(Gwindow *window) {
    Gprint_title(window);
}
static void draw_background(Gwindow *window) {
    Gfill_background(window);
}

static void print_file_names(Menu *menu) {
    for (size_t i = 0; i < menu->save_cnt; i++) {
        menu->saves[i].location = (SDL_Rect){30, 150 + i * (BUTTON_HEIGHT + 10), BUTTON_WIDTH, BUTTON_HEIGHT};
        Gtextbox(&menu->G, menu->saves[i].location, menu->saves[i].path, 5, primary);
    }
}

static void draw_new_game_options(Menu *menu) {
    char text[4][10] = {"Name:", "Width:", "Height:", "New game!"};
    int text_width[4];
    for (size_t i = 0; i < 4; i++) {
        TTF_SizeUTF8(menu->G.font_reg, text[i], &text_width[i], NULL);
    }
    SDL_Rect tmp = {60 + BUTTON_WIDTH, 150, BUTTON_WIDTH, BUTTON_HEIGHT};
    for (size_t i = 0; i < 3; i++) {
        tmp.x = 60 + BUTTON_WIDTH * 2 - text_width[i];
        Gprint(&menu->G, text[i], &tmp, primary);
        tmp.x = 60 + BUTTON_WIDTH * 2 + 10;
        Gtextbox(&menu->G, tmp, "", 5, secondary);
        if (i == 0) menu->text_input.name_rct = tmp;
        if (i == 1) menu->text_input.width_rct = tmp;
        if (i == 2) menu->text_input.height_rct = tmp;

        tmp.y += BUTTON_HEIGHT + 10;
    }
    tmp.x = 60 + BUTTON_WIDTH;
    tmp.w = BUTTON_WIDTH + BUTTON_WIDTH + 10;
    Gtextbox(&menu->G, tmp, "", 5, primary);
    tmp.x += (tmp.w - text_width[3]) / 2;
    Gprint(&menu->G, text[3], &tmp, secondary_accent);
    menu->text_input.button = tmp;

}

static void draw(Menu *menu) {
    draw_background(&menu->G);
    draw_title(&menu->G);
    print_file_names(menu);
    draw_new_game_options(menu);
    SDL_RenderPresent(menu->G.ren);
}

Menu Minit() {
    Menu menu;
    menu.G = Gnew("Game of Life by David Zoller", 3 * BUTTON_WIDTH + 100, 800, false);
    menu.saves = (Fgame_file *)malloc(MAX_SAVES * sizeof(Fgame_file));
    menu.save_cnt = Flist(menu.saves, MAX_SAVES);
    menu.game_open.G.win = NULL;
    menu.text_input.name[0] = '\0';
    menu.text_input.width[0] = '\0';
    menu.text_input.height[0] = '\0';
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
    if (SDL_PointInRect(&click, &menu->text_input.name_rct)) Ginput_text(&menu->G, menu->text_input.name, INPUT_MAX_LENGHT, menu->text_input.name_rct, true);
    if (SDL_PointInRect(&click, &menu->text_input.width_rct)) Ginput_text(&menu->G, menu->text_input.width, INPUT_MAX_LENGHT, menu->text_input.width_rct, false);
    if (SDL_PointInRect(&click, &menu->text_input.height_rct)) Ginput_text(&menu->G, menu->text_input.height, INPUT_MAX_LENGHT, menu->text_input.height_rct, false);
    if (SDL_PointInRect(&click, &menu->text_input.button)) {
        unsigned int w, h;
        if (1 != sscanf(menu->text_input.width, "%u", &w)) return;
        if (1 != sscanf(menu->text_input.height, "%u", &h)) return;
        if (w == 0 || h == 0) return;
        char *name = menu->text_input.name;
        if(name[0] == '\0' || name[0] == '.') return;
        Wclose(&menu->game_open);
        gameArea tmp = Anew(w, h);
        Aclear(&tmp);
        menu->game_open = Winit(tmp, name);
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
