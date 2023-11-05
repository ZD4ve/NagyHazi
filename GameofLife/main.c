#include <stdbool.h>

#include "include/Error.h"
// #include "include/File.h"
#include "include/Graphics.h"
#include "include/Menu.h"
#include "include/gameArea.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Ginit();
    Menu M = Minit();
    SDL_RenderPresent(M.G.ren);
    // gameArea be = Fopen("elso.con");
    // Fsave("copy.con",be);
    // Afree(&be);

    // char tmp;
    // scanf("%c",&tmp);
    SDL_Event e;
    bool quit = false;
    bool mouse_down = false;
    while (!quit) {
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_CLOSE)
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(!mouse_down){
                    mouse_down = true;
                    if(e.window.windowID == SDL_GetWindowID(M.G.win)){
                        Mclick(M,e.motion.x,e.motion.y);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                mouse_down = false;
                break;
        }
    }
    Mclose(M);
    Gquit();
    return 0;
}
