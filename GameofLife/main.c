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
    Menu M = Minit();
    SDL_RenderPresent(M.G.ren);


    SDL_Event e;
    bool quit = false;
    bool pressed[7] = {0};
    int mouse_x, mouse_y;
    /*
    0 - eger
    1 - space
    2 - jobb
    3 - bal
    4 - fel
    5 - le
    6 - ctrl
    7 - s
    */
    while (!quit) {
        SDL_WaitEvent(&e);
        SDL_GetMouseState(&mouse_x, &mouse_y);
        switch (e.type) {
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE){
                    if(e.window.windowID == SDL_GetWindowID(M.G.win)) quit = true;
                    if(e.window.windowID == SDL_GetWindowID(M.game_open.G.win)) Mclose_game(&M);
                }
                if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    Wdraw(&M.game_open);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (pressed[0]) break;
                pressed[0] = true;
                if (e.window.windowID == SDL_GetWindowID(M.G.win)) {
                    Mclick(&M, mouse_x, mouse_y);
                }
                if (e.window.windowID == SDL_GetWindowID(M.game_open.G.win)) {
                    Wclick(&M.game_open, mouse_x, mouse_y);
                }
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_RIGHT:
                        if (pressed[2]) break;
                        pressed[2] = true;
                        Astep(&M.game_open.A);
                        Wdraw(&M.game_open);
                        break;
                    case SDL_SCANCODE_LEFT:
                        if (pressed[3]) break;
                        pressed[3] = true;
                        Aback(&M.game_open.A);
                        Wdraw(&M.game_open);
                        break;
                    case SDL_SCANCODE_RCTRL:
                    case SDL_SCANCODE_LCTRL:
                        pressed[6] = true;
                        break;
                    case SDL_SCANCODE_S:
                        if (pressed[7]) break;
                        pressed[7] = true;
                        if(pressed[6]) Msave_game(&M);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEWHEEL:
                if (e.window.windowID != SDL_GetWindowID(M.game_open.G.win)) break;
                Wzoom(&M.game_open, e.wheel.preciseY, mouse_x, mouse_y);
                break;
            case SDL_MOUSEBUTTONUP:
                pressed[0] = false;
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_RIGHT:
                        pressed[2] = false;
                        break;
                    case SDL_SCANCODE_LEFT:
                        pressed[3] = false;
                        break;
                    case SDL_SCANCODE_RCTRL:
                    case SDL_SCANCODE_LCTRL:
                        pressed[6] = false;
                        break;
                    case SDL_SCANCODE_S:
                        pressed[7] = false;
                        break;
                    default:
                        break;
                }
        }
    }
    Mclose(&M);
    Gquit();
    return 0;
}
