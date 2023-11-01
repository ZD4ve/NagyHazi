#include "Error.h"
#include "File.h"
#include "Graphics.h"
#include "game_Area.h"

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    Ginit();
    Gwindow elso = Gnew("Teszt",250,500);
    GameArea be = Fopen("elso.con");
    Fsave("copy.con",be);
    (void)elso;
    (void)be;
    

    return 0;
}
