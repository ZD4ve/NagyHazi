#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <SDL2/SDL.h>
#include <stdlib.h>  //DEBUGMALLOC!!

/**
 * @brief Játéktér és tulajdonságai
 * @details Létrehozni csak fügvénnyel szabad,
 * törlése kötelező az Afree fügvénnyel
 */
typedef struct GameArea {
    uint32_t w;      // A játéktér szélessége
    uint32_t h;      // A játéktér magassága
    uint8_t **area;  // A játéktér tömbje
} GameArea;

GameArea Anew(uint32_t width, uint32_t height);
void Aclear(GameArea a);
void Afree(GameArea *a);

#endif