#ifndef DITHER_H
#define DITHER_H

#include <stdlib.h>
#include "Error.h"

/**
 * @file Dither.h
 * @brief File for functions related to ordered dithering used for cell fadeout.
 * @details Refer to https://en.wikipedia.org/wiki/Ordered_dithering for the equation source.
 */

/**
 * @brief Generates a Bayer matrix for ordered dithering.
 *
 * @param n The side length of the matrix.
 * @return A new Bayer matrix. Memory deallocation with Dfree_bayer_matrix is the caller's responsibility.
 */
size_t **Dgenerate_bayer_matrix(size_t n);

/**
 * @brief Deallocates memory used by a Bayer matrix.
 *
 * @param matrix The Bayer matrix to be freed.
 */
void Dfree_bayer_matrix(size_t **matrix);
#endif