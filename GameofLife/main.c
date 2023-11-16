/**
 * @file main.c
 * @brief Main file for the Game of Life simulator.
 *
 * This file contains the main function which initializes the graphics, 
 * creates the menu, and enters the main event loop.
 */

#include <stdlib.h>

#include "Error.h"
#include "Graphics.h"
#include "Menu.h"
#include "gameWindow.h"

/** 
 * @mainpage Game of Life by David Zoller
 *
 * \section intro_sec Introduction
 *
 * This is a Game of Life simulator implemented in C using the SDL2 library for graphics.
 * It is made as a project for the Programming 1 course at the Budapest University of Technology and Economics.
 * The Game of Life is a cellular automaton devised by the British mathematician John Horton Conway in 1970.
 * The simulator allows users to create, save, and load different game states, and control the simulation with play, pause, step forward, and step back functions.
 *
 * \section structure_sec Structure
 *
 * The project is structured into several modules:
 * - Graphics: Handles all the graphical output using the SDL2 library.
 * - Menu: Handles the main menu where users can create, load, and save games.
 * - gameWindow: Handles the window where the Game of Life simulation is displayed and controlled.
 * - GameArea: Represents the game area where the cells live.
 * - File: Handles file operations for saving and loading game states.
 * - Color: Defines the color theme used in the graphics.
 * - Dither: Provides functions for dithering colors.
 * - Error: Provides functions for error handling.
 * 
 * 
 * \section install_sec Installation
 *
 * The project uses the SDL2 and gcc libraries, which need to be installed before building the project.
 * The project can be built using the build.sh script.
 * The project can be run running the main GameOfLife executable.
 * They should be run from directory where the they are located.
 */



int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    Ginit();
    Menu M = Minit();

    SDL_Event e;
    while (1) {
        ErrorIFtrue(SDL_WaitEvent(&e) == 0, "Event hiba");
        if (e.type == SDL_USEREVENT) {
            Wevent(&M.game_open, &e);
            continue;
        }
        SDL_Window *current_window = SDL_GetKeyboardFocus();
        if (current_window == NULL) continue;
        if (current_window == M.G.win) Mevent(&M, &e);
        if (current_window == M.game_open.G.win) Wevent(&M.game_open, &e);
    }
}
