#!/bin/bash
#-fsanitize=address -g\
/usr/bin/gcc \
    -fdiagnostics-color=always \
    -g main.c source/*.c \
    -o GameofLife \
    -O3 \
    -Iinclude \
    -lSDL2 -lSDL2_gfx -lSDL2_ttf -lSDL2_image -lSDL2_mixer \
    -lm \
    -Wall -Werror -Wextra -Wpedantic