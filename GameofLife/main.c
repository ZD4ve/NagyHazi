#include <stdbool.h>

#include "include/Color.h"
#include "include/Error.h"
#include "include/File.h"
#include "include/gameArea.h"
#include "include/gameWindow.h"
#include "include/Graphics.h"
#include "include/Menu.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Ginit();
    Menu M = Minit();
    SDL_RenderPresent(M.G.ren);
    gameArea be = Fopen("saved/elso.con");
    gameWindow test = Winit(&be,"elso");
    WdrawCells(&test);
    Wrendercells(&test);
    // Fsave("copy.con",be);

    SDL_Event e;
    bool quit = false;
    bool mouse_down = false;
    while (!quit) {
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_CLOSE) quit = true;
                if(e.window.event == SDL_WINDOWEVENT_RESIZED){
                    Wrendercells(&test);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(!mouse_down){
                    mouse_down = true;
                    if(e.window.windowID == SDL_GetWindowID(M.G.win)){
                        Mclick(&M,e.motion.x,e.motion.y);
                    }
                    if(e.window.windowID == SDL_GetWindowID(test.G.win)){
                        Wclick(&test,e.motion.x,e.motion.y);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_down = false;
                break;
        }
    }
    Wclose(&test);
    Mclose(&M);
    Gquit();
    return 0;
}
