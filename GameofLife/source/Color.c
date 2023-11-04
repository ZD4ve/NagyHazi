#include "../include/Color.h"

static SDL_Color HSLtoRGB(double H, double S, double L);
static double negyzetre(double x){
    return x*x;
}

Color_theme Cinit() {
    // A program indítasa utan mindig uyganazt a szint adja vissza;
    static double PrimHue = -1;
    if (PrimHue == -1) {
        srand(time(NULL));
        PrimHue = (negyzetre((rand() / (double)RAND_MAX) * 13.4164))-90;//sqrt180 = 13.4164
    }

    Color_theme new;
    new.prim = HSLtoRGB(PrimHue, 1, .65);
    new.primacc = HSLtoRGB(PrimHue, .6, .25);
    new.sec = HSLtoRGB(PrimHue + 180, 1, .65);
    new.secacc = HSLtoRGB(PrimHue + 180, .6, .25);
    return new;
}

/**
 * @brief HSL to RGB converter
 * @param H Hue [0,360)
 * @param S Saturation [0,1]
 * @param L Lightness [0,1]
 * @details Equations from https://en.wikipedia.org/wiki/HSL_and_HSV
 */
static SDL_Color HSLtoRGB(double H, double S, double L) {
    while (H<0) H+=360;
    H = fmod(H, 360.0);
    double C = (1 - fabs(2 * L - 1)) * S;
    double H1 = H / 60;
    double X = C * (1 - fabs(fmod(H1, 2.0) - 1));
    double R1, G1, B1;
    switch ((int)H1) {
        case 0:
            R1 = C;
            G1 = X;
            B1 = 0;
            break;
        case 1:
            R1 = X;
            G1 = C;
            B1 = 0;
            break;
        case 2:
            R1 = 0;
            G1 = C;
            B1 = X;
            break;
        case 3:
            R1 = 0;
            G1 = X;
            B1 = C;
            break;
        case 4:
            R1 = X;
            G1 = 0;
            B1 = C;
            break;
        case 5:
            R1 = C;
            G1 = 0;
            B1 = X;
            break;
    }
    double m = L - C / 2;
    SDL_Color result;
    result.r = 255 * (R1 + m);
    result.g = 255 * (G1 + m);
    result.b = 255 * (B1 + m);
    result.a = 0;
    return result;
}