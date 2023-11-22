#include "Error.h"

void ErrorIFtrue_with_params(bool test, char* error_msg, char* FILE, int LINE) {
    if (!test) return;
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s\nFajl: %s\nSor: %d\nC: %s\nSDL: %s", error_msg, FILE, LINE, strerror(errno), SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void ErrorWarning(char* error_msg) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Hiba", error_msg, NULL);
    SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s\nC: %s\nSDL: %s", error_msg, strerror(errno), SDL_GetError());
}