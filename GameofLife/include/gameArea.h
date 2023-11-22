/**
 * @file gameArea.h
 * @brief This file contains the structures and functions for the gameArea,
 * where the simulation takes place and the cells live.
 */

#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Error.h"

/**
 * @struct gameArea
 * @brief Represents the game area and its properties.
 * @details This structure should only be created with a function,
 * and must be deleted with the Afree function.
 */
typedef struct gameArea {
    size_t w;      ///< Width of the game area.
    size_t h;      ///< Height of the game area.
    uint8_t **area;  ///< Array representing the game area, least significant bit is the current state, from that the next 7 bits are the history of the cell.
    uint8_t history_lenght; ///< History length of the game area, maximum 7.
} gameArea;

/**
 * @brief Creates a new game area.
 * @param width Width of the game area.
 * @param height Height of the game area.
 * @return A new game area.
 */
gameArea Anew(size_t width, size_t height);

/**
 * @brief Clears the game area.
 * @param gamearea Pointer to the game area to clear. Must not be NULL.
 */
void Aclear(gameArea *gamearea);

/**
 * @brief Frees the memory allocated for the game area.
 * @param gamearea Pointer to the game area to free. Must not be NULL.
 */
void Afree(gameArea *gamearea);

/**
 * @brief Gets the age of a cell.
 * @param cell The cell to get the age of.
 * @return The age of the cell.
 */
ssize_t Agetage(uint8_t cell);

/**
 * @brief Advances the simulation by one step.
 * @param A Pointer to the game area to step. Must not be NULL.
 */
void Astep(gameArea *A);

/**
 * @brief Steps back the simulation by one step.
 * @param A Pointer to the game area to step back. Must not be NULL.
 * @return True if successful, false otherwise.
 */
bool Aback(gameArea *A);

/**
 * @brief Flips a cell in the game area.
 * @param A Pointer to the game area. Must not be NULL.
 * @param x The x-coordinate of the cell to flip.
 * @param y The y-coordinate of the cell to flip.
 * @remark If the coordinates are out of bounds, the function does nothing.
 */
void Aflipcell(gameArea *A, double x, double y);

#endif