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
    Menu M = Minit();
    SDL_RenderPresent(M.G.ren);
    gameArea be = Fopen("saved/test.con");
    gameWindow test = Winit(&be, "elso");
    Wdraw(&test, true);
    // Fsave("copy.con",be);

    SDL_Event e;
    bool quit = false;
    bool pressed[5] = {0};
    /*
    0 - eger
    1 - space
    2 - jobb
    3 - bal
    4 - fel
    5 - le
    */
    while (!quit) {
        SDL_WaitEvent(&e);
        switch (e.type) {
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE) quit = true;
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    Wdraw(&test, false);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (pressed[0]) break;
                pressed[0] = true;
                if (e.window.windowID == SDL_GetWindowID(M.G.win)) {
                    Mclick(&M, e.motion.x, e.motion.y);
                }
                if (e.window.windowID == SDL_GetWindowID(test.G.win)) {
                    Wclick(&test, e.motion.x, e.motion.y);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                pressed[0] = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.scancode) {
                    //space
                    case SDL_SCANCODE_RIGHT:
                        if(pressed[2]) break;
                        pressed[2] = true;
                        Astep(&test.A);
                        Wdraw(&test, true);
                        break;
                    default: break;
                }
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.scancode) {
                    //space
                    case SDL_SCANCODE_RIGHT:
                        pressed[2] = false;
                        break;
                    default: break;
                }
        }
    }
    Wclose(&test);
    Mclose(&M);
    Gquit();
    return 0;
}
