#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/**
 * @file Color.h
 * @brief Header file for color-related structures and functions.
 */

/**
 * @enum Colortype
 * @brief Represents different color types for rendering.
 */
typedef enum Colortype 
{ 
    primary, 
    secondary,
    primary_accent,
    secondary_accent
} Colortype;

/**
 * @struct Color_theme
 * @brief Represents a color theme with 5 colors.
 */
typedef struct Color_theme {
    SDL_Color prim;    /**< Primary color */
    SDL_Color primacc; /**< Primary accent color */
    SDL_Color sec;     /**< Secondary color */
    SDL_Color secacc;  /**< Secondary accent color */
    SDL_Color bg;      /**< Background color */
} Color_theme;


/**
 * @brief Initializes a Color_theme with a dynamically generated color scheme.
 *
 * @details This function initializes a Color_theme structure with dynamically generated
 * colors based on a random hue value that has a higher probability to be a warm color.
 * From this hue, a complement color is generated for the secondary. The function ensures
 * that if called multiple times, it returns the same theme.
 *
 * @return A Color_theme structure representing the generated color scheme.
 */
Color_theme Cinit();
#endif