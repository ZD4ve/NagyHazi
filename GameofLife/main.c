#include <stdbool.h>

#include "include/Color.h"
#include "include/Error.h"
#include "include/File.h"
#include "include/Graphics.h"
#include "include/Menu.h"
#include "include/gameArea.h"
#include "include/gameWindow.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Ginit();
    //SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
    Menu M = Minit();
    SDL_RenderPresent(M.G.ren);


    SDL_Event e;
    //bool quit = false;
    while (1) {
        SDL_WaitEvent(&e);
        SDL_Window *current_window = SDL_GetKeyboardFocus(); //SDL_GetMouseFocus();
        if(current_window == NULL) continue;
        if(current_window == M.G.win) Mevent(&M,e);
        if(current_window == M.game_open.G.win) Wevent(&M.game_open,e);
    }
}
