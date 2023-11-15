#ifndef ERROR_H
#define ERROR_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#define ErrorIFtrue(test, error_msg) ErrorIFtrue_with_params(test, error_msg, __FILE__, __LINE__);
#define ErrorIFnull(ptr, error_msg) ErrorIFtrue_with_params(ptr == NULL, error_msg, __FILE__, __LINE__);
#define ErrorIFsdl(func_with_negative_error) ErrorIFtrue_with_params(func_with_negative_error < 0, "SDL hiba!", __FILE__, __LINE__);
#define ErrorIFnoMemory(ptr) ErrorIFtrue_with_params(ptr == NULL, "Nincs eleg memoria!", __FILE__, __LINE__);

void ErrorIFtrue_with_params(bool test, char* error_msg, char* FILE, int LINE);

#endif