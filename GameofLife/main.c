#include "include/Error.h"
#include "include/File.h"
#include "include/Graphics.h"
#include "include/gameArea.h"

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    Ginit();
    Gwindow elso = Gnew("Teszt",250,500);
    gameArea be = Fopen("elso.con");
    Fsave("copy.con",be);
    (void)elso;
    (void)be;
    

    return 0;
}
