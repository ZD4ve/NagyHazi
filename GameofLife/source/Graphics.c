#include "../include/Graphics.h"

void Ginit() {
    ErrorIFtrue(SDL_Init(SDL_INIT_EVERYTHING) < 0, "Nem indithato az SDL!");
    SDL_SetHint("SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR", "0");
    SDL_SetHint(SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH, "1");
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
    window.ren = SDL_CreateRenderer(window.win, -1, SDL_RENDERER_SOFTWARE);
    ErrorIFnull(window.ren, "Nem hozhato letre a megjelenito!");
    window.font_big = TTF_OpenFont("asset/PixelifySans.ttf", 72);
    ErrorIFtrue(!window.font_big, "Nem sikerult megnyitni a fontot!");
    window.font_reg = TTF_OpenFont("asset/born2bsporty-fs.otf", 24);
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

static SDL_Rect print_with_font(Gwindow *window, char *text, SDL_Rect location, SDL_Color color, TTF_Font *font) {
    if (text[0] == '\0') return location;
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
    return location;
}

SDL_Rect Gprint(Gwindow *window, char *text, SDL_Rect *location, Colortype col) {
    SDL_Color szin;
    if (col == primary) szin = window->colors.prim;
    if (col == primary_accent) szin = window->colors.primacc;
    if (col == secondary) szin = window->colors.sec;
    if (col == secondary_accent) szin = window->colors.secacc;
    return print_with_font(window, text, *location, szin, window->font_reg);
}

void Gprint_title(Gwindow *window) {
    char title[] = "Game of Life";
    SDL_Rect location;
    ErrorIFtrue(TTF_SizeUTF8(window->font_big, title, &location.w, &location.h) < 0, "TTF hiba!");
    location.x = (window->w - location.w) / 2;  // kozepre rendezes
    location.y = 30;
    print_with_font(window, "Game of Life", location, window->colors.prim, window->font_big);
}

void Gtextbox(Gwindow *window, char *text, SDL_Rect *location, Colortype col, size_t border_width) {
    Gset_color(window, col == primary ? window->colors.primacc : window->colors.secacc);
    SDL_RenderFillRect(window->ren, location);
    SDL_Rect inside_rect = *location;
    inside_rect.x += border_width;
    inside_rect.y += border_width;
    inside_rect.w -= border_width * 2;
    inside_rect.h -= border_width * 2;
    Gset_color(window, col == primary ? window->colors.prim : window->colors.sec);
    SDL_RenderFillRect(window->ren, &inside_rect);
    inside_rect.x += border_width;
    print_with_font(window, text, inside_rect, col == primary ? window->colors.secacc : window->colors.primacc, window->font_reg);
}

SDL_Texture *Gpre_render_cells(Gwindow *window) {
    SDL_Texture *tex = SDL_CreateTexture(
        window->ren,
        SDL_GetWindowPixelFormat(window->win),
        SDL_TEXTUREACCESS_TARGET,
        8 * CELL_SIZE, CELL_SIZE);
    SDL_SetRenderTarget(window->ren, tex);
    size_t **matrix = Dgenerate_bayer_matrix(CELL_SIZE);
    double fade_out[8] = {1, 0.3, 0.2, 0.15, 0.1, 0.05, 0, 0};
    ssize_t top_left_edge = CELL_SIZE / 8 - 1;
    if (top_left_edge < 0) top_left_edge = 0;
    ssize_t bottom_right_edge = CELL_SIZE - CELL_SIZE / 8;
    for (size_t i = 0; i < 8; i++) {
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

void Ginput_text(Gwindow *window, char *dest, size_t len, SDL_Rect rect, bool is_file_name) {
    /* Ez tartalmazza az aktualis szerkesztest */
    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';
    /* Ezt a kirajzolas kozben hasznaljuk */
    char textandcomposition[len + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];
    bool quit = false;
    bool done = false;
    if (dest[0] != '\0' && is_file_name) dest[strlen(dest) - 4] = '\0';

    SDL_StartTextInput();
    while (!quit & !done) {
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        Gtextbox(window, textandcomposition, &rect, primary, 5);
        SDL_RenderPresent(window->ren);

        SDL_Event e;
        SDL_WaitEvent(&e);
        switch (e.type) {
            /* Kulonleges karakter */
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    int textlen = strlen(dest);
                    do {
                        if (textlen == 0) {
                            break;
                        }
                        if ((dest[textlen - 1] & 0x80) == 0x00) {
                            /* Egy bajt */
                            dest[textlen - 1] = 0x00;
                            break;
                        }
                        if ((dest[textlen - 1] & 0xC0) == 0x80) {
                            /* Bajt, egy tobb-bajtos szekvenciabol */
                            dest[textlen - 1] = 0x00;
                            textlen--;
                        }
                        if ((dest[textlen - 1] & 0xC0) == 0xC0) {
                            /* Egy tobb-bajtos szekvencia elso bajtja */
                            dest[textlen - 1] = 0x00;
                            break;
                        }
                    } while (true);
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    done = true;
                }
                break;

            /* A feldolgozott szoveg bemenete */
            case SDL_TEXTINPUT:
                if (strlen(dest) + strlen(e.text.text) < len) {
                    strcat(dest, e.text.text);
                }

                /* Az eddigi szerkesztes torolheto */
                composition[0] = '\0';
                break;

            /* Szoveg szerkesztese */
            case SDL_TEXTEDITING:
                strcpy(composition, e.edit.text);
                break;

            /* A felhasznalo kikattint a szovegdobozbol */
            case SDL_MOUSEBUTTONDOWN: {
                SDL_Point mouse_position;
                SDL_GetMouseState(&mouse_position.x, &mouse_position.y);
                if (!SDL_PointInRect(&mouse_position, &rect)) {
                    SDL_PushEvent(&e);
                    done = true;
                }
                break;
            }
            /* Ablak bezarasa*/
            case SDL_WINDOWEVENT:
                if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                    SDL_PushEvent(&e);
                    quit = true;
                }
                break;
        }
    }
    SDL_StopTextInput();
    if (done) {
        if (is_file_name) strcat(dest, ".con");
        Gtextbox(window, dest, &rect, secondary, 5);
        SDL_RenderPresent(window->ren);
    }
}
