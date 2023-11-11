#include "../include/gameWindow.h"

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
    new.texture_w = new.A.w *CELL_SIZE;
    new.texture_h = new.A.h *CELL_SIZE;
    new.pre_rendered_cells = Gpre_render_cells(&new.G);
    new.full_game = SDL_CreateTexture(new.G.ren, SDL_GetWindowPixelFormat(new.G.win), SDL_TEXTUREACCESS_TARGET, new.texture_w, new.texture_h);
    Wresetzoom(&new);
    Wdraw(&new);
    return new;
}
void Wclose(gameWindow *game) {
    if (game->G.win == NULL) return;
    Afree(&game->A);
    SDL_DestroyTexture(game->pre_rendered_cells);
    SDL_DestroyTexture(game->full_game);
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
    Wdraw(game);
}

void Wdraw(gameWindow *game) {
    Gset_color(&game->G, game->G.colors.bg);
    SDL_RenderClear(game->G.ren);
    SDL_FPoint target_point = {0.0, 0.0};
    SDL_Rect target = {0, 0, CELL_SIZE * game->zoom + 1, CELL_SIZE * game->zoom + 1};
    SDL_Rect source = {0, 0, CELL_SIZE, CELL_SIZE};
    for (size_t x = 0; x < game->A.w; x++) {
        for (size_t y = 0; y < game->A.h; y++) {
            source.x = CELL_SIZE * Agetage(game->A.area[x][y]);
            target_point = map_game_to_screen(game, (SDL_FPoint){x, y});
            target.x = target_point.x;
            target.y = target_point.y;
            SDL_RenderCopy(game->G.ren, game->pre_rendered_cells, &source, &target);
            // a rendercopy eldobja magatol a kijelzon kivuli rajzolasokat
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
    Wdraw(game);
}
void Wresetzoom(gameWindow *game) {
    int win_w, win_h;
    SDL_GetRendererOutputSize(game->G.ren, &win_w, &win_h);
    game->zoom = kissebb(win_w / (double)game->texture_w, win_h / (double)game->texture_h);
    game->x_screen_offset = (win_w - game->texture_w * game->zoom) / 2;
    game->y_screen_offset = (win_h - game->texture_h * game->zoom) / 2;
}
void Wevent(gameWindow *game, SDL_Event e) {
    static bool pressed[9] = {0};
    /*
    0 - eger
    1 - space
    2 - jobb
    3 - bal
    4 - fel
    5 - le
    6 - ctrl
    7 - s
    8 - r
    */
    int mouse_x, mouse_y;
    SDL_GetMouseState(&mouse_x, &mouse_y);
    switch (e.type) {
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_CLOSE)
                Wclose(game);
            if (e.window.event == SDL_WINDOWEVENT_RESIZED){
                Wresetzoom(game);
                Wdraw(game);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (pressed[0]) break;
            pressed[0] = true;
            Wclick(game, mouse_x, mouse_y);
            break;
        case SDL_KEYDOWN:
            switch (e.key.keysym.scancode) {
                case SDL_SCANCODE_SPACE:
                    if (pressed[1]) break;
                    pressed[1] = true;
                    break;
                case SDL_SCANCODE_RIGHT:
                    if (pressed[2]) break;
                    pressed[2] = true;
                    Astep(&game->A);
                    Wdraw(game);
                    break;
                case SDL_SCANCODE_LEFT:
                    if (pressed[3]) break;
                    pressed[3] = true;
                    Aback(&game->A);
                    Wdraw(game);
                    break;
                case SDL_SCANCODE_UP:
                    if (pressed[4]) break;
                    pressed[4] = true;
                    break;
                case SDL_SCANCODE_DOWN:
                    if (pressed[5]) break;
                    pressed[5] = true;
                    break;
                case SDL_SCANCODE_RCTRL:
                case SDL_SCANCODE_LCTRL:
                    pressed[6] = true;
                    break;
                case SDL_SCANCODE_S:
                    if (pressed[7]) break;
                    pressed[7] = true;
                    if (pressed[6])
                        Fsave(game->name, &game->A);
                    break;
                case SDL_SCANCODE_R:
                    if (pressed[8]) break;
                    pressed[8] = true;
                    Wresetzoom(game);
                default:
                    break;
            }
            break;
        case SDL_MOUSEWHEEL:
            Wzoom(game, e.wheel.preciseY, mouse_x, mouse_y);
            break;
        case SDL_MOUSEBUTTONUP:
            pressed[0] = false;
            break;
        case SDL_KEYUP:
            switch (e.key.keysym.scancode) {
                case SDL_SCANCODE_SPACE:
                    pressed[0] = false;
                    break;
                case SDL_SCANCODE_RIGHT:
                    pressed[2] = false;
                    break;
                case SDL_SCANCODE_LEFT:
                    pressed[3] = false;
                    break;
                case SDL_SCANCODE_UP:
                    pressed[4] = false;
                    break;
                case SDL_SCANCODE_DOWN:
                    pressed[5] = false;
                    break;
                case SDL_SCANCODE_RCTRL:
                case SDL_SCANCODE_LCTRL:
                    pressed[6] = false;
                    break;
                case SDL_SCANCODE_S:
                    pressed[7] = false;
                    break;
                case SDL_SCANCODE_R:
                    pressed[8] = false;
                    break;
                default:
                    break;
            }
    }
}
