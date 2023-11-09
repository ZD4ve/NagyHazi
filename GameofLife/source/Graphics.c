#include "../include/Graphics.h"

void Ginit() {
    ErrorIFtrue(SDL_Init(SDL_INIT_EVERYTHING) < 0, "Nem indithato az SDL!");
    ErrorIFtrue(TTF_Init() < 0, "TTF elinditasa sikertelen");
}
void Gclose(Gwindow *window) {
    TTF_CloseFont(window->font_big);
    TTF_CloseFont(window->font_reg);
    SDL_DestroyRenderer(window->ren);
    SDL_DestroyWindow(window->win);
    window->ren = NULL;
    window->win = NULL;
}
void Gquit() {
    TTF_Quit();
    SDL_Quit();
}

Gwindow Gnew(char title[], int width, int height, bool resizable) {
    Gwindow window;
    window.h = height;
    window.w = width;
    window.win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI | (resizable & SDL_WINDOW_RESIZABLE));
    ErrorIFnull(window.win, "Nem hozhato letre az ablak!");
    window.ren = SDL_CreateRenderer(window.win, -1, SDL_RENDERER_ACCELERATED);
    ErrorIFnull(window.ren, "Nem hozhato letre a megjelenito!");
    window.font_big = TTF_OpenFont("asset/PixelifySans.ttf", 48);
    ErrorIFtrue(!window.font_big, "Nem sikerult megnyitni a fontot!");
    window.font_reg = TTF_OpenFont("asset/PixelifySans.ttf", 24);
    ErrorIFtrue(!window.font_reg, "Nem sikerult megnyitni a fontot!");
    window.colors = Cinit();
    return window;
}

void Gset_color(Gwindow *window, SDL_Color col) {
    SDL_SetRenderDrawColor(window->ren, col.r, col.g, col.b, col.a);
}

void Gfill_background(Gwindow *window) {
    Gset_color(window, window->colors.bg);
    SDL_RenderClear(window->ren);
}

static void Gprint_with_font(Gwindow *window, char *text, SDL_Rect location, SDL_Color color, TTF_Font *font) {
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    ErrorIFnull(surface, "Sikertelen surface render!");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->ren, surface);
    ErrorIFnull(texture, "Sikertelen texture render!");
    location.y += (location.h - surface->h) / 2;
    location.w = surface->w;
    location.h = surface->h;
    ErrorIFtrue(SDL_RenderCopy(window->ren, texture, NULL, &location) < 0, "Sikertelen render!");
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/*static Uint32 color_to_int(SDL_Color color) {
    return SDL_MapRGBA(&format, color.r, color.g, color.b, color.a);
}*/

void Gprint(Gwindow *window, char *text, SDL_Rect *location, Colortype col) {
    Gprint_with_font(window, text, *location, col == primary ? window->colors.primacc : window->colors.secacc, window->font_reg);
}

void Gprint_title(Gwindow *window) {
    char title[] = "Game of Life";
    SDL_Rect location;
    ErrorIFtrue(TTF_SizeUTF8(window->font_big, title, &location.w, &location.h) < 0, "TTF hiba!");
    location.x = (window->w - location.w) / 2;  // kozepre rendezes
    location.y = 30;
    Gprint_with_font(window, "Game of Life", location, window->colors.prim, window->font_big);
}

SDL_Rect Grectwithborders(Gwindow *window, SDL_Rect location, size_t border_width, Colortype col) {
    Gset_color(window, col == primary ? window->colors.primacc : window->colors.secacc);
    SDL_RenderFillRect(window->ren, &location);
    location.x += border_width;
    location.y += border_width;
    location.w -= border_width * 2;
    location.h -= border_width * 2;
    Gset_color(window, col == primary ? window->colors.prim : window->colors.sec);
    SDL_RenderFillRect(window->ren, &location);
    return location;
}

SDL_Texture *Gpre_render_cells(Gwindow *window) {
    SDL_Texture *tex = SDL_CreateTexture(
        window->ren,
        SDL_GetWindowPixelFormat(window->win),
        SDL_TEXTUREACCESS_TARGET,
        9 * CELL_SIZE, CELL_SIZE);
    SDL_SetRenderTarget(window->ren, tex);
    size_t **matrix = Dgenerate_bayer_matrix(CELL_SIZE);
    double fade_out[9] = {1, 0.3, 0.2, 0.15, 0.1, 0.05, 0, 0, 0};
    ssize_t top_left_edge = CELL_SIZE / 8 - 1;
    if (top_left_edge < 0) top_left_edge = 0;
    ssize_t bottom_right_edge = CELL_SIZE - CELL_SIZE / 8;
    for (size_t i = 0; i < 9; i++) {
        for (size_t x = 0; x < CELL_SIZE; x++) {
            for (size_t y = 0; y < CELL_SIZE; y++) {
                bool isalive = matrix[x][y] < (size_t)(fade_out[i] * CELL_SIZE * CELL_SIZE);
                bool isedge =
                    x <= (size_t)top_left_edge ||
                    y <= (size_t)top_left_edge ||
                    x >= (size_t)bottom_right_edge ||
                    y >= (size_t)bottom_right_edge;
                if (isalive & !isedge) Gset_color(window, window->colors.prim);
                if (isalive & isedge) Gset_color(window, window->colors.primacc);
                if (!isalive & !isedge) Gset_color(window, window->colors.bg);
                if (!isalive & isedge) Gset_color(window, window->colors.secacc);
                SDL_RenderDrawPoint(window->ren, x + (CELL_SIZE * i), y);
            }
        }
    }
    SDL_RenderPresent(window->ren);
    SDL_SetRenderTarget(window->ren, NULL);
    Dfree_bayer_matrix(matrix);
    return tex;
}
