/**
 * @file Menu.h
 * @brief This file contains the structures and functions for the menu window.
 */

#ifndef MENU_H
#define MENU_H

#include <stdlib.h>

#include "File.h"
#include "Graphics.h"
#include "gameWindow.h"

/**
 * @brief Number of saves listed in the menu.
 */
#define MAX_SAVES 13
/**
 * @brief Maximum length for the text inputs.
 */
#define INPUT_MAX_LENGHT 20

/**
 * @brief Represents the input for a new game.
 */
typedef struct uj_jatek_input {
    char name[INPUT_MAX_LENGHT + 4];  ///< The name of the new game.
    SDL_Rect name_rct;                ///< The text box for the name input.
    char width[INPUT_MAX_LENGHT];     ///< The width of the new game.
    SDL_Rect width_rct;               ///< The text box for the width input.
    char height[INPUT_MAX_LENGHT];    ///< The height of the new game.
    SDL_Rect height_rct;              ///< The text box for the height input.
    SDL_Rect button;                  ///< The bounding box for the new game button.
} uj_jatek_input;

/**
 * @brief Represents the menu and its properties.
 * @details This structure should only be created with Minit, and must be deleted with the Mclose function.
 */
typedef struct Menu {
    Gwindow G;                  ///< The graphics window.
    Fgame_file *saves;          ///< The saved games.
    size_t save_cnt;            ///< The count of saved games.
    gameWindow game_open;       ///< The open game window.
    uj_jatek_input text_input;  ///< The input for a new game.
} Menu;

/**
 * @brief Initializes the menu.
 * @return The menu.
 */
Menu Minit();

/**
 * @brief Closes the menu.
 * @param menu Pointer to the menu to close. Must not be NULL.
 */
void Mclose(Menu *menu);

/**
 * @brief Handles a click event in the menu.
 * @param menu Pointer to the menu. Must not be NULL.
 * @param x The x-coordinate of the click.
 * @param y The y-coordinate of the click.
 */
void Mclick(Menu *menu, int x, int y);

/**
 * @brief Handles an event in the menu.
 * @param menu Pointer to the menu to handle event. Must not be NULL.
 * @param e The event to handle. Must not be NULL.
 */
void Mevent(Menu *menu, SDL_Event *e);

#endif