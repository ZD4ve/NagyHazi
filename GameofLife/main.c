#include "include/Error.h"
#include "include/File.h"
#include "include/Graphics.h"
#include "include/gameArea.h"
#include "include/Menu.h"

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    Ginit();
    //Gwindow elso = Gnew("Teszt",250,500);
    //gameArea be = Fopen("elso.con");
    //Fsave("copy.con",be);
    Gwindow win = Minit();
    //(void)elso;
    //(void)be;
    while(1);
    
    Gclose(win);
    Gquit();
    return 0;
}
