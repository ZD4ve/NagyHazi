#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Error.h"
#include "debugmalloc.h"


/**
 * @brief Játéktér és tulajdonságai
 * @details Létrehozni csak fügvénnyel szabad,
 * törlése kötelező az Afree fügvénnyel
 */
typedef struct gameArea {
    size_t w;      // A játéktér szélessége
    size_t h;      // A játéktér magassága
    uint8_t **area;  // A játéktér tömbje
    uint8_t history_lenght;
} gameArea;

gameArea Anew(size_t width, size_t height);
void Aclear(gameArea *gamearea);
void Afree(gameArea *gamearea);
size_t Agetage(uint8_t cell);
void Astep(gameArea *A);
bool Aback(gameArea *A);
void Aflipcell(gameArea *A, double x, double y);

#endif