#include "../include/File.h"

gameArea Fopen(char *path) {
    char err[] = "Serult fajl!";
    FILE *file = fopen(path, "r");
    ErrorIFnull(file, "Nem sikerult megnyitni a fajlt!");
    size_t w_in, h_in;
    ErrorIFtrue(fscanf(file, "%lu %lu", &w_in, &h_in) != 2, err);
    ErrorIFtrue(w_in == 0 || h_in == 0, err);
    gameArea gamearea = Anew(w_in, h_in);
    while (fgetc(file) != '\n') ErrorIFtrue(feof(file), err);
    char read;
    for (size_t y = 0; y < gamearea.h; y++) {
        for (size_t x = 0; x < gamearea.w; x++) {
            ErrorIFtrue(feof(file), err);
            read = fgetc(file);
            ErrorIFtrue(read != '.' && read != 'O', err);
            gamearea.area[x][y] = (read == 'O');
        }
        if (getc(file) == '\r') getc(file);
    }
    fclose(file);
    return gamearea;
}
void Fsave(char *path, gameArea gamearea) {
    FILE *file = fopen(path, "w");
    ErrorIFnull(file, "Nem sikerult menteni a fajlt!");
    fprintf(file, "%lu %lu\n", gamearea.w, gamearea.h);
    for (size_t y = 0; y < gamearea.h; y++) {
        for (size_t x = 0; x < gamearea.w; x++) {
            putc((gamearea.area[x][y] & 1u) == 0 ? '.' : 'O', file);
        }
        putc('\n', file);
    }
    fclose(file);
}

size_t Flist(Fgame_file games[], size_t max_count){
    DIR *mappa = opendir("saved");
    size_t cnt = max_count;
    for (size_t i = 0; i < max_count; i++)
    {
        struct dirent *fajl = readdir(mappa);
        if(fajl == NULL) {
            cnt = i;
            break;
        }
        if(fajl->d_name[0]=='.'){--i; continue;}
        games[i].path = (char*)malloc((strlen(fajl->d_name)+1)*sizeof(char));
        strcpy(games[i].path,fajl->d_name);
    }
    closedir(mappa);
    return cnt;
}
