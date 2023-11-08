#include "../include/gamearea.h"

gameArea Anew(size_t width, size_t height) {
    gameArea new = {
        .w = width,
        .h = height,
        .history_lenght = 0,
    };
    new.area = (uint8_t **)malloc(width * sizeof(uint8_t *));
    ErrorIFnull(new.area, "Sikertelen memoria foglalas!");
    new.area[0] = (uint8_t *)malloc(width * height * sizeof(uint8_t));
    ErrorIFnull(new.area[0], "Sikertelen memoria foglalas!");
    for (size_t x = 1; x < width; ++x)
        new.area[x] = new.area[0] + x *height;
    return new;
}

void Aclear(gameArea *gamearea) {
    for (size_t x = 0; x < gamearea->w; x++) {
        for (size_t y = 0; y < gamearea->h; y++) {
            gamearea->area[x][y] = 0;
        }
    }
}

void Afree(gameArea *gamearea) {
    gamearea->h = 0;
    gamearea->w = 0;
    free(gamearea->area[0]);
    free(gamearea->area);
    gamearea->area = NULL;
}

size_t Agetage(uint8_t cell) {
    for (size_t i = 0; i < 8; i++) {
        if ((cell & (1 << i)) != 0) return i;
    }
    return 8;
}
static bool isalive(uint8_t cell) {
    // megnezzuk, hogy a masodik legkisseb helyirteken 1 van-e
    return (cell >> 1) & 1;
}
static bool isvaidcord(ssize_t x, ssize_t y, size_t w, size_t h) {
    return 0 <= x && (size_t)x < w &&
           0 <= y && (size_t)y < h;
}
void Astep(gameArea *A) {
    for (size_t x = 0; x < A->w; x++) {
        for (size_t y = 0; y < A->h; y++) {
            A->area[x][y] <<= 1;
        }
    }
    for (size_t x = 0; x < A->w; x++) {
        for (size_t y = 0; y < A->h; y++) {
            size_t sum = 0;
            for (ssize_t x_offset = -1; x_offset <= 1; x_offset++) {
                for (ssize_t y_offset = -1; y_offset <= 1; y_offset++) {
                    if (x_offset == 0 && y_offset == 0) continue;
                    sum += isvaidcord(x + x_offset, y + y_offset, A->w, A->h) &&
                           isalive(A->area[x + x_offset][y + y_offset]);
                }
            }
            A->area[x][y] |= isalive(A->area[x][y]) ? (sum == 2 || sum == 3) : (sum == 3);
        }
    }
    if (A->history_lenght != 7) A->history_lenght++;
}
bool Aback(gameArea *A) {
    if (A->history_lenght == 0) return false;
    for (size_t x = 0; x < A->w; x++) {
        for (size_t y = 0; y < A->h; y++) {
            A->area[x][y] >>= 1;
        }
    }
    if (A->history_lenght != 0) A->history_lenght--;
    return true;
}
void Aflipcell(gameArea *A, ssize_t x, ssize_t y) {
    if(x >= (ssize_t)A->w || y >= (ssize_t)A->h || x<0 || y<0) return;
    //ErrorIFtrue(x >= A->w || y >= A->h || x<0 || y<0, "Cella lehelyezes nem letezo helyre!");
    A->area[x][y] ^= 1;
    A->history_lenght = 0;
}