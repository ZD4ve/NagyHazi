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
    SDL_FPoint new_place_on_screen = map_game_to_screen(game,orginal_place_in_game);
    game->x_screen_offset += x-new_place_on_screen.x;
    game->y_screen_offset += y-new_place_on_screen.y;
    Wdraw(game);
}
void Wresetzoom(gameWindow *game){
    int win_w, win_h;
    SDL_GetRendererOutputSize(game->G.ren, &win_w, &win_h);
    game->zoom = kissebb(win_w / (double)game->texture_w, win_h / (double)game->texture_h);
    game->x_screen_offset = (win_w-game->texture_w*game->zoom)/2;
    game->y_screen_offset = (win_h-game->texture_h*game->zoom)/2;
}

