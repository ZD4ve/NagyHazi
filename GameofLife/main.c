#include "include/Error.h"
// #include "include/File.h"
#include "include/Graphics.h"
#include "include/Menu.h"
#include "include/gameArea.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Ginit();
    Gwindow win = Minit();
    SDL_RenderPresent(win.ren);
    // gameArea be = Fopen("elso.con");
    // Fsave("copy.con",be);
    // Afree(&be);

    // char tmp;
    // scanf("%c",&tmp);
    SDL_Event e;
    while (1) {
        SDL_WaitEvent(&e);
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
            break;
            //if (SDL_GetWindowID(myWindowA) == e.window.windowID) {}
        }
    }

    Gclose(win);
    Gquit();
    return 0;
}
