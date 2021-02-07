#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void libInit();
void errorLog();
void cleanUp();

void createWindows(SDL_Window **window1, SDL_Window **window2);
void closeEvent(SDL_Window **window1, SDL_Window **window2, int *openMain, int *openDev);