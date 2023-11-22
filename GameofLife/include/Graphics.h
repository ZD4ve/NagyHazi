/**
 * @file Graphics.h
 * @brief This file contains code used for graphics.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include "Color.h"
#include "Dither.h"
#include "Error.h"

/**
 * @def CELL_SIZE
 * @brief The size of a rendered cell in pixels.
 * @details It should be a power of 2. Smaller values will result in better performance, but worse quality.
 */
#define CELL_SIZE 8

/**
 * @struct Gwindow
 * @brief Represents the graphics window and its properties.
 */
typedef struct Gwindow {
    SDL_Window *win;     ///< The SDL window.
    SDL_Renderer *ren;   ///< The SDL renderer.
    size_t w, h;         ///< The width and height of the window.
    TTF_Font *font_big;  ///< The font used for the title.
    TTF_Font *font_reg;  ///< The font used for regular text.
    Color_theme colors;  ///< The color theme.
} Gwindow;

/**
 * @brief Initializes SDL2.
 * @warning This function must be called before any other function.
 */
void Ginit();

/**
 * @brief Creates a new window.
 * @param title The title of the window. Must not be NULL.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param resizable Whether the window is resizable or not.
 * @return A new window.
 */
Gwindow Gnew(char title[], int width, int height, bool resizable);

/**
 * @brief Closes the graphics window.
 * @param window Pointer to the graphics window to close. Must not be NULL.
 */
void Gclose(Gwindow *window);

/**
 * @brief Quits the SDL2 application.
 * @remark exit() should be called after this function.
 */
void Gquit();

/**
 * @brief Sets the color of the renderer.
 * @param window Pointer to the window to set color. Must not be NULL.
 * @param col The color to set.
 */
void Gset_color(Gwindow *window, SDL_Color col);

/**
 * @brief Fills the background of the Menu.
 * @param window Pointer to the window to fill background. Must not be NULL.
 */
void Gfill_background(Gwindow *window);

/**
 * @brief Prints the title of the game.
 * @param window Pointer to the window to print title. Must not be NULL.
 */
void Gprint_title(Gwindow *window);

/**
 * @brief Prints text in the graphics window.
 * @param window Pointer to the window to print text. Must not be NULL.
 * @param text The text to print. Empty string for no text. Must not be NULL.
 * @param location The location to print the text.
 * @param col The color of the text.
 * @return The rectangle where the text was printed.
 */
SDL_Rect Gprint(Gwindow *window, char *text, SDL_Rect *location, Colortype col);

/**
 * @brief Creates a textbox in the graphics window.
 * @param window Pointer to the window to create textbox. Must not be NULL.
 * @param text The text for the textbox. Empty string for no text. Must not be NULL.
 * @param location The location for the textbox.
 * @param col The color of the textbox, only accepts primary or secondary.
 * @param border_width The width of the border of the textbox.
 */
void Gtextbox(Gwindow *window, char *text, SDL_Rect *location, Colortype col, size_t border_width);

/**
 * @brief Pre-renders cells in the graphics window.
 * @param window Pointer to the game window. Must not be NULL.
 * @return The texture of the pre-rendered cells.
 * @remark It uses the ordered dithering algorithm to render the fading effect.
 * @file Dither.h
 */
SDL_Texture *Gpre_render_cells(Gwindow *window);

/**
 * @brief Handles text input in the graphics window.
 * @param window Pointer to the window to handle text input. Must not be NULL.
 * @param dest The destination for the input text.
 * @param lenght The length of the input text.
 * @param bounding_box The bounding box for the input text.
 * @param is_file_name Whether the input text is a file name or not.
 * If it is, it will append ".con" to the end, and the destination must be 4 bytes longer than lenght.
 */
void Ginput_text(Gwindow *window, char *dest, size_t lenght, SDL_Rect bounding_box, bool is_file_name);

#endif