#include "game_Area.h"

static void malloc_test(void *p) {
    if (p != NULL) return;
    SDL_Log("Nincs elég memória!");
    exit(EXIT_FAILURE);
}

GameArea Anew(uint32_t width, uint32_t height) {
    GameArea new = {
        .w = width,
        .h = height,
    };
    new.area = (uint8_t **)malloc(width * sizeof(uint8_t *));
    malloc_test(new.area);
    new.area[0] = (uint8_t *)malloc(width * height * sizeof(uint8_t));
    malloc_test(new.area[0]);
    for (size_t x = 1; x < width; ++x)
        new.area[x] = new.area[0] + x *height;
    return new;
}

void Aclear(GameArea a) {
    for (size_t x = 0; x < a.w; x++) {
        for (size_t y = 0; y < a.h; y++) {
            a.area[x][y] = 0;
        }
    }
}

void Afree(GameArea *a) {
    a->h = 0;
    a->w = 0;
    free(a->area[0]);
    free(a->area);
    a->area = NULL;
}