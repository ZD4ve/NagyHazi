#include "game_Area.h"



GameArea Anew(size_t width, size_t height) {
    GameArea new = {
        .w = width,
        .h = height,
    };
    new.area = (uint8_t **)malloc(width * sizeof(uint8_t *));
    ErrorIFnull(new.area, "Sikertelen memoria foglalas!");
    new.area[0] = (uint8_t *)malloc(width * height * sizeof(uint8_t));
    ErrorIFnull(new.area[0], "Sikertelen memoria foglalas!");
    for (size_t x = 1; x < width; ++x)
        new.area[x] = new.area[0] + x *height;
    return new;
}

void Aclear(GameArea gamearea) {
    for (size_t x = 0; x < gamearea.w; x++) {
        for (size_t y = 0; y < gamearea.h; y++) {
            gamearea.area[x][y] = 0;
        }
    }
}

void Afree(GameArea *gamearea) {
    gamearea->h = 0;
    gamearea->w = 0;
    free(gamearea->area[0]);
    free(gamearea->area);
    gamearea->area = NULL;
}