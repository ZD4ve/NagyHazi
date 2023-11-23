/**
 * @file Color.h
 * @brief This file contains color-related structures and functions.
 */

#ifndef COLOR_H
#define COLOR_H

#include <SDL2/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief An enumeration representing different color types for rendering.
 */
typedef enum Colortype {
    primary,         /**< Primary color type */
    secondary,       /**< Secondary color type */
    primary_accent,  /**< Primary accent color type */
    secondary_accent /**< Secondary accent color type */
} Colortype;

/**
 * @brief A structure representing a color theme with five colors.
 */
typedef struct Color_theme {
    SDL_Color prim;    /**< Primary color of the theme */
    SDL_Color primacc; /**< Primary accent color of the theme */
    SDL_Color sec;     /**< Secondary color of the theme */
    SDL_Color secacc;  /**< Secondary accent color of the theme */
    SDL_Color bg;      /**< Background color of the theme */
} Color_theme;

/**
 * @brief Initializes a Color_theme with a dynamically generated color scheme.
 * @remarks This function initializes a Color_theme structure with dynamically generated
 * colors based on a random hue value that has a higher probability to be a warm color.
 * From this hue, a complement color is generated for the secondary. The function ensures
 * that if called multiple times, it returns the same theme.
 * @return A Color_theme structure representing the generated color scheme.
 */
Color_theme Cinit();

#endif