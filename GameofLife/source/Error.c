#include "Error.h"

void ErrorIFtrue_with_params(bool test, char* error_msg, char* FILE, int LINE) {
    if (!test) return;
    SDL_Log("%s\nFajl: %s\nSor: %d\nSDL: %s", error_msg, FILE, LINE, SDL_GetError());
    //abort();
    SDL_Quit();
    exit(EXIT_FAILURE);
}