#include "gameWindow.h"

#define DEFAULT_WIDTH 1000
#define DEFAULT_HEIGHT 500

static double kissebb(double a, double b) {
    return a < b ? a : b;
}

gameWindow Winit(gameArea A, char *name) {
    gameWindow new;
    new.A = A;
    new.name = name;
    new.G = Gnew(new.name, DEFAULT_WIDTH, DEFAULT_HEIGHT, true);
    new.pre_rendered_cells = Gpre_render_cells(&new.G);
    new.autoplay_id = 0;
    new.autoplay_delay = 500;
    Wresetzoom(&new);
    Wdraw(&new, true);
    return new;
}
void Wclose(gameWindow *game) {
    if (game->G.win == NULL) return;
    if (game->autoplay_id != 0)
        SDL_RemoveTimer(game->autoplay_id);
    Afree(&game->A);
    SDL_DestroyTexture(game->pre_rendered_cells);
    Gclose(&game->G);
}

static SDL_FPoint map_screen_to_game(gameWindow *game, SDL_FPoint screen_point) {
    return (SDL_FPoint){
        .x = (screen_point.x - game->x_screen_offset) / (CELL_SIZE * game->zoom),
        .y = (screen_point.y - game->y_screen_offset) / (CELL_SIZE * game->zoom)};
}
static SDL_FPoint map_game_to_screen(gameWindow *game, SDL_FPoint game_point) {
    return (SDL_FPoint){
        .x = ((game_point.x * CELL_SIZE * game->zoom) + game->x_screen_offset),
        .y = ((game_point.y * CELL_SIZE * game->zoom) + game->y_screen_offset)};
}

void Wclick(gameWindow *game, int x, int y) {
    SDL_FPoint pont = map_screen_to_game(game, (SDL_FPoint){(float)x, (float)y});
    Aflipcell(&game->A, pont.x, pont.y);
}

void Wdraw(gameWindow *game, bool all_cells) {
    Gset_color(&game->G, game->G.colors.bg);
    if (all_cells)
        ErrorIFsdl(SDL_RenderClear(game->G.ren));
    SDL_FPoint target_point = {0.0, 0.0};
    SDL_Rect target = {0, 0, CELL_SIZE * game->zoom + 1, CELL_SIZE * game->zoom + 1};
    SDL_Rect source = {0, 0, CELL_SIZE, CELL_SIZE};
    for (size_t x = 0; x < game->A.w; x++) {
        for (size_t y = 0; y < game->A.h; y++) {
            ssize_t age = Agetage(game->A.area[x][y]);
            if (all_cells || age != -1) {
                source.x = (age == -1 ? 7 : age) * CELL_SIZE;
                target_point = map_game_to_screen(game, (SDL_FPoint){x, y});
                target.x = target_point.x;
                target.y = target_point.y;
                ErrorIFsdl(SDL_RenderCopy(game->G.ren, game->pre_rendered_cells, &source, &target));
                // a rendercopy eldobja magatol a kijelzon kivuli rajzolasoka
            }
        }
    }
    SDL_RenderPresent(game->G.ren);
}
void Wzoom(gameWindow *game, double wheel, int x, int y) {
    SDL_FPoint orginal_place_in_game = map_screen_to_game(game, (SDL_FPoint){x, y});
    game->zoom *= 1 + 0.1 * wheel;
    SDL_FPoint new_place_on_screen = map_game_to_screen(game, orginal_place_in_game);
    game->x_screen_offset += x - new_place_on_screen.x;
    game->y_screen_offset += y - new_place_on_screen.y;
    Wdraw(game, true);
}
void Wresetzoom(gameWindow *game) {
    int win_w, win_h;
    ErrorIFsdl(SDL_GetRendererOutputSize(game->G.ren, &win_w, &win_h));
    game->zoom = kissebb((double)win_w / (game->A.w*CELL_SIZE), (double)win_h / (game->A.h*CELL_SIZE));
    game->x_screen_offset = (win_w - game->A.w*CELL_SIZE * game->zoom) / 2;
    game->y_screen_offset = (win_h - game->A.h*CELL_SIZE * game->zoom) / 2;
}
static bool too_fast() {
    int number_of_events = SDL_PeepEvents(NULL, 1, SDL_PEEKEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT);
    ErrorIFsdl(number_of_events);
    return number_of_events == 1;
}

void Wspeed(gameWindow *game, bool faster) {
    if (too_fast())
        faster = false;
    if (faster) {
        game->autoplay_delay /= 2;
        if (game->autoplay_delay == 0)
            game->autoplay_delay = 1;
    } else {
        game->autoplay_delay *= 2;
    }
}
static Uint32 autostep(Uint32 interval, void *game) {
    (void)interval;
    SDL_Event e;
    e.type = SDL_USEREVENT;
    e.user.code = too_fast() ? 1 : 0;
    ErrorIFsdl(SDL_PushEvent(&e));
    return ((gameWindow *)game)->autoplay_delay;
}
void Wtoggle_autoplay(gameWindow *game) {
    if (game->autoplay_id == 0) {
        game->autoplay_id = SDL_AddTimer(1, autostep, (void *)game);
        ErrorIFtrue(game->autoplay_id == 0, "Sikertelen autoplay inditas!");
    } else {
        SDL_RemoveTimer(game->autoplay_id);
        game->autoplay_id = 0;
    }
}
static bool first_click(SDL_Event *e, bool *state) {
    if (e->type == SDL_KEYDOWN) {
        if (!*state) {
            *state = true;
            return true;
        } else {
            return false;
        }
    } else {
        *state = false;
        return false;
    }
}
static void keyevent(gameWindow *game, SDL_Event *e) {
    static bool key_pressed[8] = {0};
    /*
    0 - r
    1 - space
    2 - jobb
    3 - bal
    4 - fel
    5 - le
    6 - ctrl
    7 - s
    */
    switch (e->key.keysym.scancode) {
        case SDL_SCANCODE_R:
            if (!first_click(e, &key_pressed[0])) break;
            Wresetzoom(game);
            Wdraw(game, true);
            break;
        case SDL_SCANCODE_SPACE:
            if (!first_click(e, &key_pressed[1])) break;
            Wtoggle_autoplay(game);
            break;
        case SDL_SCANCODE_RIGHT:
            if (!first_click(e, &key_pressed[2])) break;
            Astep(&game->A);
            Wdraw(game, false);
            break;
        case SDL_SCANCODE_LEFT:
            if (!first_click(e, &key_pressed[3])) break;
            Aback(&game->A);
            Wdraw(game, true);
            break;
        case SDL_SCANCODE_UP:
            if (!first_click(e, &key_pressed[4])) break;
            if (game->autoplay_id != 0)
                Wspeed(game, true);
            break;
        case SDL_SCANCODE_DOWN:
            if (!first_click(e, &key_pressed[5])) break;
            if (game->autoplay_id != 0)
                Wspeed(game, false);
            break;
        case SDL_SCANCODE_RCTRL:
        case SDL_SCANCODE_LCTRL:
            first_click(e, &key_pressed[6]);
            break;
        case SDL_SCANCODE_S:
            if (!first_click(e, &key_pressed[7])) break;
            if (key_pressed[6])
                Fsave(game->name, &game->A);
            break;
        default:
            break;
    }
}

void Wevent(gameWindow *game, SDL_Event *e) {
    static bool mouse_down = false;
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    switch (e->type) {
        case SDL_WINDOWEVENT:
            if (e->window.event == SDL_WINDOWEVENT_CLOSE)
                Wclose(game);
            if (e->window.event == SDL_WINDOWEVENT_RESIZED) {
                // Wresetzoom(game);
                Wdraw(game, true);
            }
            break;
        case SDL_USEREVENT:
            if (e->user.code == 0) {
                Astep(&game->A);
                Wdraw(game, false);
            }
            if (e->user.code == 1) {
                Wspeed(game, false);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (mouse_down) break;
            mouse_down = true;
            Wclick(game, mouse_x, mouse_y);
            Wdraw(game, true);
            break;
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            keyevent(game, e);
            break;
        case SDL_MOUSEWHEEL:
            Wzoom(game, e->wheel.preciseY, mouse_x, mouse_y);
            break;
        case SDL_MOUSEBUTTONUP:
            mouse_down = false;
            break;
    }
}
