#include <stdlib.h>

#include "include/Graphics.h"
#include "include/Menu.h"
#include "include/gameWindow.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Ginit();
    Menu M = Minit();
    
    SDL_Event e;
    while (1) {
        SDL_WaitEvent(&e);
        if (e.type == SDL_USEREVENT) {
            Wevent(&M.game_open, &e);
            continue;
        }
        SDL_Window *current_window = SDL_GetKeyboardFocus();
        if (current_window == NULL) continue;
        if (current_window == M.G.win) Mevent(&M, &e);
        if (current_window == M.game_open.G.win) Wevent(&M.game_open, &e);
    }
}
