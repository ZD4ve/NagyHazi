#include "Error.h"

void ErrorIFnull(void* ptr, char* error_msg) {
    ErrorIFtrue(ptr == NULL, error_msg);
}

void ErrorIFtrue(bool test, char* error_msg) {
    if (!test) return;
    SDL_Log("%s\n%s", error_msg, SDL_GetError());
    exit(EXIT_FAILURE);
}