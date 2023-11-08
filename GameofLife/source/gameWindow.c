#include "../include/gameWindow.h"

#define DEFAULT_WIDTH 1000
#define DEFAULT_HEIGHT 500

gameWindow Winit(gameArea *A, char *name) {
    gameWindow new;
    new.A = *A;
    new.name = name;
    new.G = Gnew(new.name, DEFAULT_WIDTH, DEFAULT_HEIGHT, true);
    new.zoom = 15;
    new.texture_w = CELL_SIZE *new.A.w;
    new.texture_h = CELL_SIZE *new.A.h;
    new.center_x = new.texture_w / 2.0-20;
    new.center_y = new.texture_h / 2.0+20;
    new.pre_rendered_cells = Gpre_render_cells(&new.G);
    new.full_game = SDL_CreateTexture(new.G.ren, SDL_GetWindowPixelFormat(new.G.win), SDL_TEXTUREACCESS_TARGET, new.texture_w, new.texture_h);
    return new;
}
void Wclose(gameWindow *game) {
    Afree(&game->A);
    SDL_DestroyTexture(game->pre_rendered_cells);
    SDL_DestroyTexture(game->full_game);
    Gclose(&game->G);
}

void Wclick(gameWindow *game, int x, int y) {
    int win_w, win_h;
    SDL_GetRendererOutputSize(game->G.ren, &win_w, &win_h);
    Aflipcell(&game->A,
              ((x-win_w/2)/game->zoom+game->center_x)/CELL_SIZE,
              ((y-win_h/2)/game->zoom+game->center_y)/CELL_SIZE);
    WdrawCells(game);
    Wrendercells(game);
}

void WdrawCells(gameWindow *game) {
    SDL_SetRenderTarget(game->G.ren, game->full_game);
    SDL_Rect target = {0, 0, CELL_SIZE, CELL_SIZE};
    SDL_Rect source = {0, 0, CELL_SIZE, CELL_SIZE};
    for (size_t x = 0; x < game->A.w; x++) {
        for (size_t y = 0; y < game->A.h; y++) {
            source.x = CELL_SIZE * Agetage(game->A.area[x][y]);
            target.x = x * CELL_SIZE;
            target.y = y * CELL_SIZE;
            SDL_RenderCopy(game->G.ren, game->pre_rendered_cells, &source, &target);
        }
    }
    SDL_RenderPresent(game->G.ren);
    SDL_SetRenderTarget(game->G.ren, NULL);
}
void Wrendercells(gameWindow *game) {
    Gset_color(&game->G, game->G.colors.bg);
    SDL_RenderClear(game->G.ren);
    SDL_Rect target = {.x = 0, .y = 0};
    SDL_GetRendererOutputSize(game->G.ren, &target.w, &target.h);
    SDL_Rect source;
    source.w = target.w / game->zoom;
    source.h = target.h / game->zoom;
    source.x = game->center_x - source.w / 2.0;
    source.y = game->center_y - source.h / 2.0;
    if (source.x < 0) {
        target.x = -source.x * game->zoom;
        target.w += source.x * game->zoom;
        source.x = 0;
    }
    if (source.y < 0) {
        target.y = -source.y * game->zoom;
        target.h += source.y * game->zoom;
        source.y = 0;
    }
    if ((source.x + source.w) > (int)game->texture_w) {
        source.w = (game->texture_w - source.x);
        target.w = (game->texture_w - source.x) * game->zoom;
    }
    if ((source.y + source.h) > (int)game->texture_h) {
        source.h = (game->texture_h - source.y);
        target.h = (game->texture_h - source.y) * game->zoom;
    }
    SDL_RenderCopy(game->G.ren, game->full_game, &source, &target);
    SDL_RenderPresent(game->G.ren);
}