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
}
void Gquit() {
    TTF_Quit();
    SDL_Quit();
}

Gwindow Gnew(char title[], int width, int height) {
    Gwindow window;
    window.h = height;
    window.w = width;
    window.win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
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

static void set_color(Gwindow *window, SDL_Color col) {
    SDL_SetRenderDrawColor(window->ren, col.r, col.g, col.b, col.a);
}

void Gfill_background(Gwindow *window) {
    set_color(window, window->colors.bg);
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

static Uint32 color_to_int(SDL_Color color) {
    return SDL_MapRGBA(SDL_PIXELFORMAT_RGBA8888, color.r, color.g, color.b, color.a);
}

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
    set_color(window, col == primary ? window->colors.primacc : window->colors.secacc);
    SDL_RenderFillRect(window->ren, &location);
    location.x += border_width;
    location.y += border_width;
    location.w -= border_width * 2;
    location.h -= border_width * 2;
    set_color(window, col == primary ? window->colors.prim : window->colors.sec);
    SDL_RenderFillRect(window->ren, &location);
    return location;
}

SDL_Texture *Gpre_render_cells(Gwindow *window) {
    SDL_Surface *sur = SDL_CreateRGBSurface(0, 9 * CELL_SIZE, CELL_SIZE, 32, 0, 0, 0, 0);
    SDL_Rect cell_outline = {0, 0, CELL_SIZE, CELL_SIZE};
    SDL_Rect cell_inside = {0, 0, CELL_SIZE - (2 * CELL_SIZE / 8), CELL_SIZE - 2 * CELL_SIZE / 8};
    for (size_t i = 0; i < 9; i++) {
        cell_outline.x += CELL_SIZE;
        cell_inside.x += CELL_SIZE;
        SDL_FillRect(sur, &cell_outline, color_to_int(i == 0 ? window->colors.primacc : window->colors.secacc));
        SDL_FillRect(sur, &cell_inside, color_to_int(i == 0 ? window->colors.prim : window->colors.bg));
        // TODO: elhalvanyulas+orderes dithering
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(window->ren, sur);
    SDL_FreeSurface(sur);
    return tex;
    // SDL_Texture *new = SDL_CreateTexture(window->ren,SDL_GetWindowPixelFormat(window->win),SDL_TEXTUREACCESS_STATIC,8*CELL_SIZE,CELL_SIZE);
}