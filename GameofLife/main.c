#include <stdlib.h>

#include "Error.h"
#include "Graphics.h"
#include "Menu.h"
#include "gameWindow.h"

/**
 * @mainpage Game of Life by David Zoller
 *  
 * @section intro_sec Introduction
 *
 * This is a Game of Life simulator implemented in C using the SDL2 library for graphics.
 * It is made as a project for the Programming 1 course at the Budapest University of Technology and Economics. \n
 * The simulator allows users to create, save, and load different game states, and control the simulation with play,
 * pause, step forward, and step back functions.
 *
 * @subsection conway_sec Conway's Game of Life
 *
 * The Game of Life, also known simply as Life, is a cellular automaton devised
 * by the British mathematician John Horton Conway in 1970. It is a zero-player game,
 * meaning that its evolution is determined by its initial state, requiring no further
 * input. One interacts with the Game of Life by creating an initial configuration and
 * observing how it evolves. It is Turing complete and can simulate a universal constructor
 * or any other Turing machine.
 *
 * @subsection rules_sec Rules
 *
 * The universe of the Game of Life is an infinite (this simulator only works on finite grids),
 * two-dimensional orthogonal grid of square cells, each of which is in one of two possible states,
 * live or dead (or populated and unpopulated, respectively). Every cell interacts with its eight neighbours,
 * which are the cells that are horizontally, vertically, or diagonally adjacent. At each step in time, the following transitions occur:
 * - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
 * - Any live cell with two or three live neighbours lives on to the next generation.
 * - Any live cell with more than three live neighbours dies, as if by overpopulation.
 * - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
 *
 * The generations are created by applying the above rules simultaneously to every cell in the seed, live or dead;
 * births and deaths occur simultaneously, and the discrete moment at which this happens is sometimes called a tick.
 * Each generation is a pure function of the preceding one.
 * @see  Source: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
 *
 * @section structure_sec Structure
 *
 * The project is structured into several modules:
 * - Graphics.h: Handles all the graphical output using the SDL2 library.
 * - Menu.h: Handles the main menu where users can create, load, and save games.
 * - gameWindow.h: Handles the window where the simulation is displayed and controlled.
 * - gameArea.h: Represents the game area where the cells live.
 * - File.h: Handles file operations for saving and loading game states.
 * - Color.h: Defines the color theme used in the graphics.
 * - Dither.h: Provides functions for dithering colors.
 * - Error.h: Provides functions for error handling.
 *
 * The state of the cells are stored in a 2D array of 8bit unsigned integers,
 * where the LSB represents the current state of the cell, and the other 7 bits
 * represent the history of the cell. This allows for the simulation to be run
 * in reverse for 7 ticks and to show the decay of the cells. \n
 * For example: \n
 * \c 00000000 - Dead cell \n
 * \c 00000010 - Dead cell, was alive 1 tick ago \n
 * \c 01010001 - Alive cell, was alive 4 and 6 ticks ago
 *
 * @section file_sec File Format (.con)
 *
 * The first line of the file specifies the dimensions of the game board,
 * separated by spaces (width first, then height).
 * Additional data can be stored within the same line.
 * The game board follows next. Here, empty cells are represented by a dot,
 * while living cells are represented by a capital 'O'.
 * These are stored in a grid layout. The file type is ".con". \n
 * For example: elso.con \n
 * <tt>
 * 7 3     \n
 * .....O. \n
 * OOO..O. \n
 * .....O. \n
 * </tt>
 *
 * @section install_sec Installation
 *
 * The project uses the \c SDL2 and \c gcc libraries,
 * which need to be installed before building the project.
 * The project can be built using the build.sh script.
 * The project can be run by running the main GameOfLife executable.
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
