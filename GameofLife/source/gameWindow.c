#include "../include/gameWindow.h"

gameWindow Winit(gameArea *A) {
    gameWindow new;
    new.A = *A;
    // new.G = uj ablak, ujrameretezheto
    Gpre_render_cells(new.G);
    new.full_game = SDL_CreateTexture(new.G.ren, SDL_GetWindowPixelFormat(new.G.win), SDL_TEXTUREACCESS_TARGET, CELL_SIZE * new.A.w, CELL_SIZE * new.A.h);
    return new;
}
void Wclose(gameWindow *game) {
    Afree(&game->A);
    SDL_DestroyTexture(game->pre_rendered_cells);
    SDL_DestroyTexture(game->full_game);
    Gclose(game->G);
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
    SDL_SetRenderTarget(game->G.ren, NULL);
}