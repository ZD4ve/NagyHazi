/**
 * @file File.h
 * @brief File operations for the game.
 */

#ifndef FILE_H
#define FILE_H

#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "Error.h"
#include "gameArea.h"

#define SAVES_FOLDER "saved/" ///< Directory for saved games.

/**
 * @brief Structure representing a game file.
 */
typedef struct Fgame_file{
    char *path; ///< Path to the game file.
    SDL_Rect location; ///< Location of the opening button on screen.
} Fgame_file;

/**
 * @brief Opens a game file.
 * @param path Path to the game file. Must be a valid path.
 * @return The game area.
 */
gameArea Fopen(char *path);

/**
 * @brief Saves a game area to a file.
 * @param path Path to the game file. Should be a valid path.
 * @param gamearea Pointer to the game area to save.
 */
void Fsave(char *path, gameArea *gamearea);

/**
 * @brief Lists game files.
 * @param games Array of game files. Must not be NULL.
 * @param max_count Maximum number of game files to list.
 * @return The number of game files listed.
 */
size_t Flist(Fgame_file games[], size_t max_count);

#endif