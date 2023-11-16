#include "Menu.h"
#include "debugmalloc.h"

#define BUTTON_HEIGHT 40
#define BUTTON_WIDTH 200

static void draw_title(Menu *menu) {
    Gprint_title(&menu->G);
}
static void draw_background(Menu *menu) {
    Gfill_background(&menu->G);
}
static void print_file_names(Menu *menu) {
    for (size_t i = 0; i < menu->save_cnt; i++) {
        menu->saves[i].location = (SDL_Rect){30, 150 + i * (BUTTON_HEIGHT + 10), BUTTON_WIDTH, BUTTON_HEIGHT};
        Gtextbox(&menu->G, menu->saves[i].path, &menu->saves[i].location, primary, 5);
    }
}
static void draw_new_game_options(Menu *menu) {
    char text[4][10] = {"Name:", "Width:", "Height:", "New game!"};
    int text_width[4];
    for (size_t i = 0; i < 4; i++) {
        ErrorIFsdl(TTF_SizeUTF8(menu->G.font_reg, text[i], &text_width[i], NULL));
    }
    SDL_Rect tmp = {60 + BUTTON_WIDTH, 150, BUTTON_WIDTH, BUTTON_HEIGHT};
    for (size_t i = 0; i < 3; i++) {
        tmp.x = 60 + BUTTON_WIDTH * 2 - text_width[i];
        Gprint(&menu->G, text[i], &tmp, primary);
        tmp.x = 60 + BUTTON_WIDTH * 2 + 10;
        Gtextbox(&menu->G, "", &tmp, secondary, 5);
        if (i == 0) menu->text_input.name_rct = tmp;
        if (i == 1) menu->text_input.width_rct = tmp;
        if (i == 2) menu->text_input.height_rct = tmp;

        tmp.y += BUTTON_HEIGHT + 10;
    }
    tmp.x = 60 + BUTTON_WIDTH;
    tmp.w = BUTTON_WIDTH + BUTTON_WIDTH + 10;
    Gtextbox(&menu->G, "", &tmp, primary, 5);
    tmp.x += (tmp.w - text_width[3]) / 2;
    Gprint(&menu->G, text[3], &tmp, secondary_accent);
    menu->text_input.button = tmp;
}
static void draw_keys(Menu *menu) {
    SDL_Rect target = {BUTTON_WIDTH + 60, 4 * (BUTTON_HEIGHT + 10) + 150, BUTTON_HEIGHT, BUTTON_HEIGHT};
    char tips[9][20] = {"One step", "One step back", "Speed up", "Slow down", "Reset Zoom", "Start the sim", "Place cell", "Zoom", "Save"};
    char keys[9][20] = {"→", "←", " ↑ ", " ↓ "," R ", "SPACE", "Click", "Wheel", "Ctrl + S"};
    for (size_t i = 0; i < 9; i++) {
        if (i >= 5) target.w = BUTTON_WIDTH/2;
        Gprint(&menu->G, tips[i], &target, primary);
        target.x += BUTTON_WIDTH + 10;
        Gtextbox(&menu->G, keys[i], &target, primary, 5);
        target.x -= BUTTON_WIDTH + 10;
        target.y += BUTTON_HEIGHT + 10;
    }
}

static void draw(Menu *menu) {
    draw_background(menu);
    draw_title(menu);
    print_file_names(menu);
    draw_new_game_options(menu);
    draw_keys(menu);
    SDL_RenderPresent(menu->G.ren);
}

Menu Minit() {
    Menu menu;
    menu.G = Gnew("Game of Life by David Zoller", 3 * BUTTON_WIDTH + 100, 820, false);
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
        if (name[0] == '\0' || name[0] == '.') return;
        Wclose(&menu->game_open);
        gameArea tmp = Anew(w, h);
        Aclear(&tmp);
        menu->game_open = Winit(tmp, name);
    }
}
void Mevent(Menu *menu, SDL_Event *e) {
    static bool mouse_down = false;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    switch (e->type) {
        case SDL_WINDOWEVENT:
            if (e->window.event == SDL_WINDOWEVENT_CLOSE) {
                Mclose(menu);
                Gquit();
                SDL_Quit();
                exit(EXIT_SUCCESS);
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
