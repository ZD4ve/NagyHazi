/**
 * @file gameWindow.h
 * @brief This file contains the structures and functions for the game window.
 */

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <stdbool.h>
#include "Graphics.h"
#include "gameArea.h"
#include "File.h"

/**
 * @struct gameWindow
 * @brief Represents the game window and its properties.
 * @details This structure should only be created with a function, and must be deleted with the Wclose function.
 */
typedef struct gameWindow {
    gameArea A; ///< The game area.
    Gwindow G; ///< The graphics window.
    char *name; ///< The name of the game window.
    SDL_Texture *pre_rendered_cells; ///< The pre-rendered cells.
    double zoom; ///< The zoom level.
    ssize_t x_screen_offset; ///< The x-coordinate screen offset.
    ssize_t y_screen_offset; ///< The y-coordinate screen offset.
    SDL_TimerID autoplay_id; ///< The autoplay timer ID.
    Uint32 autoplay_delay; ///< The autoplay delay.
} gameWindow;

/**
 * @brief Initializes a new game window.
 * @param A The game area.
 * @param name The name of the game window.
 * @return A new game window.
 */
gameWindow Winit(gameArea A, char *name);

/**
 * @brief Closes the game window.
 * @param game Pointer to the game window to close.
 */
void Wclose(gameWindow *game);

/**
 * @brief Handles a click event in the game window.
 * @param game Pointer to the game window.
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 */
void Wclick(gameWindow *game, int x, int y);

/**
 * @brief Draws the game window.
 * @param game Pointer to the game window to draw.
 * @param all_cells Whether to draw all cells or just the ones that changed.
 */
void Wdraw(gameWindow *game, bool all_cells);

/**
 * @brief Zooms the game window.
 * @param game Pointer to the game window to zoom.
 * @param wheel The amount to zoom.
 * @param x The x-coordinate of the zoom center.
 * @param y The y-coordinate of the zoom center.
 */
void Wzoom(gameWindow *game, double wheel, int x, int y);

/**
 * @brief Resets the zoom level of the game window.
 * @param game Pointer to the game window to reset zoom.
 */
void Wresetzoom(gameWindow *game);

/**
 * @brief Handles an event in the game window.
 * @param game Pointer to the game window to handle event.
 * @param e The event to handle.
 */
void Wevent(gameWindow *game, SDL_Event *e);

#endif