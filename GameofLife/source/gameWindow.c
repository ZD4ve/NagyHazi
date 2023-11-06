#include "../include/gameWindow.h"

gameWindow Winit(gameArea A){
    gameWindow new;
    new.A = A;
    //new.G = uj ablak
    Gpre_render_cells(new.G);
    new.full_game = SDL_CreateTexture(new.G.ren,SDL_GetWindowPixelFormat(new.G.win),SDL_TEXTUREACCESS_TARGET,CELL_SIZE*A.w,CELL_SIZE*A.h);
    return new;
}
void Wclose(gameWindow W){
    Afree(&W.A);
    SDL_DestroyTexture(W.pre_rendered_cells);
    SDL_DestroyTexture(W.full_game);
    Gclose(W.G);
}