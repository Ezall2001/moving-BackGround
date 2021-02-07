#include "common.h"

void errorLog(char *msg, const char *log)
{
  printf("%s: %s\n", msg, log);
}

void libInit()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    errorLog("failed at SDL_Init", SDL_GetError());

  int flags = IMG_INIT_JPG | IMG_INIT_PNG;
  int IMG_Mask = IMG_Init(flags);
  if (IMG_Mask & flags != flags)
    errorLog("failed at IMG_Init", IMG_GetError());
}

void createWindows(SDL_Window **window1, SDL_Window **window2)
{

  *window1 = SDL_CreateWindow("moving background", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 400, 0);
  if (*window1 == NULL)
    errorLog("failed at create mainWindow", SDL_GetError());
  *window2 = SDL_CreateWindow("what is really happening", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2000, 400, 0);
  if (*window2 == NULL)
    errorLog("failed at create devWindow", SDL_GetError());

  int centerX, centerY;
  SDL_GetWindowPosition(*window1, &centerX, &centerY);
  SDL_SetWindowPosition(*window1, centerX, centerY + 300);

  SDL_GetWindowPosition(*window2, &centerX, &centerY);
  SDL_SetWindowPosition(*window2, centerX, centerY - 300);
}

void closeEvent(SDL_Window **window1, SDL_Window **window2, int *openMain, int *openDev)
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    if (event.type == SDL_WINDOWEVENT)
    {
      if (event.window.event == SDL_WINDOWEVENT_CLOSE)
      {
        int windowId = event.window.windowID;
        if (windowId == 1)
        {
          *openMain = 0;
          SDL_DestroyWindow(*window1);
        }
        else if (windowId == 2)
        {
          *openDev = 0;
          SDL_DestroyWindow(*window2);
        }
      }
    }
  }
}

void cleanUp()
{
  IMG_Quit();
  SDL_Quit();
}