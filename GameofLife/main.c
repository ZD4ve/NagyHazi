#include "include/Error.h"
#include "include/File.h"
#include "include/Graphics.h"
#include "include/gameArea.h"
#include "include/Menu.h"

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    Ginit();
    Gwindow win = Minit();

    gameArea be = Fopen("elso.con");
    Fsave("copy.con",be);
    Afree(&be);

    char tmp;
    scanf("%c",&tmp);

    Gclose(win);
    Gquit();
    return 0;
}
