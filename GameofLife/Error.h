#ifndef ERROR_H
#define ERROR_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

void ErrorIFnull(void* ptr, char* error_msg);
void ErrorIFtrue(bool test, char* error_msg);

#endif