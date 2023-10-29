#include <stdio.h>
#include "Graphics.h"


int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    Ginit();
    Gwindow elso = Gnew("Teszt",250,500);
    (void)elso;
    

    return 0;
}
