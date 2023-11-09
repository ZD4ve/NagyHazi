#ifndef DITHER_H
#define DITHER_H

#include <stdlib.h>
#include "debugmalloc.h"

size_t **Dgenerate_bayer_matrix(size_t n);
void Dfree_bayer_matrix(size_t **matrix);
#endif