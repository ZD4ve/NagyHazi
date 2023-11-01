#include "../include/Graphics.h"

static TTF_Font *Gfont_big;
static TTF_Font *Gfont_reg;

void Ginit() {
    ErrorIFtrue(SDL_Init(SDL_INIT_EVERYTHING) < 0, "Nem indithato az SDL!");
    ErrorIFtrue(TTF_Init()<0,"TTF elinditasa sikertelen");
    Gfont_big = TTF_OpenFont("asset/PixelifySans.ttf", 48);
    ErrorIFtrue(!Gfont_big, "Nem sikerult megnyitni a fontot!");
    Gfont_reg = TTF_OpenFont("asset/PixelifySans.ttf", 20);
    ErrorIFtrue(!Gfont_reg, "Nem sikerult megnyitni a fontot!");
}

void Gquit() {
    TTF_CloseFont(Gfont_big);
    TTF_CloseFont(Gfont_reg);
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
    return window;
}

static void Gprint_with_font(Gwindow window, char *text, SDL_Rect location, SDL_Color color, TTF_Font *font){
    SDL_Surface *surface = TTF_RenderUTF8_Blended(font, text, color);
    ErrorIFnull(surface,"Sikertelen surface render!");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window.ren, surface);
    ErrorIFnull(texture,"Sikertelen texture render!");
    ErrorIFtrue(SDL_RenderCopy(window.ren, texture, NULL, &location)<0,"Sikertelen render!");
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void Gprint(Gwindow window, char *text, SDL_Rect location, SDL_Color color) {
    Gprint_with_font(window,text,location,color,Gfont_reg);
}

void Gprint_title(Gwindow window, SDL_Color color) {
    char title[] = "Game of Life";
    SDL_Rect location;
    ErrorIFtrue(TTF_SizeUTF8(Gfont_big,title,&location.w,&location.h)<0,"TTF hiba!");
    location.x = (window.w-location.w)/2;//kozepre rendezes
    location.y = 30;
    Gprint_with_font(window,"Game of Life",location,color,Gfont_big);

}