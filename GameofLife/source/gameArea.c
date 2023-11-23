#include "gameArea.h"

#include "debugmalloc.h"

gameArea Anew(size_t width, size_t height) {
    gameArea new = {
        .w = width,
        .h = height,
        .history_lenght = 0,
    };
    new.area = (uint8_t **)malloc(width * sizeof(uint8_t *));
    ErrorIFnoMemory(new.area);
    new.area[0] = (uint8_t *)malloc(width * height * sizeof(uint8_t));
    ErrorIFnoMemory(new.area[0]);
    for (size_t x = 1; x < width; ++x)
        new.area[x] = new.area[0] + x *height;
    return new;
}

void Aclear(gameArea *gamearea) {
    memset(gamearea->area[0], 0, gamearea->w * gamearea->h * sizeof(uint8_t));
}

void Afree(gameArea *gamearea) {
    gamearea->h = 0;
    gamearea->w = 0;
    free(gamearea->area[0]);
    free(gamearea->area);
    gamearea->area = NULL;
}

ssize_t Agetage(uint8_t cell) {
    if (cell == 0) return -1;
    for (size_t i = 0; i < 8; i++) {
        if ((cell & (1 << i)) != 0) return i;
    }
    return -1;  // ez sose kéne hogy lefusson
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
void Aflipcell(gameArea *A, double x, double y) {
    if (x >= (double)A->w || y >= (double)A->h || x < 0 || y < 0) return;
    A->area[(int)x][(int)y] ^= 1;
    A->history_lenght = 0;
}