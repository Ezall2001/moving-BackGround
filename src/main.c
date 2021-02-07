#include "common.h"

int main(int argc, char *argv[])
{

  libInit(); // A

  ////////////////////////////////////////////// B
  // window creation
  SDL_Window *mainWindow = NULL, *devWindow = NULL;
  createWindows(&mainWindow, &devWindow);

  // reading the image data
  SDL_RWops *birdIMG = SDL_RWFromFile("./assets/bird.png", "rb");
  SDL_RWops *backgroundIMG = SDL_RWFromFile("./assets/background.png", "rb");
  SDL_RWops *cameraIMG = SDL_RWFromFile("./assets/camera.png", "rb");

  if (!birdIMG || !backgroundIMG || !cameraIMG)
    errorLog("failed at reading PNG", IMG_GetError());

  // getting main surfaces
  SDL_Surface *mainScreen = NULL, *devScreen = NULL, *background = NULL, *bird = NULL, *camera = NULL;

  mainScreen = SDL_GetWindowSurface(mainWindow);
  devScreen = SDL_GetWindowSurface(devWindow);

  if (!mainScreen || !devScreen)
    errorLog("failed at getting surface", SDL_GetError());

  // loading images
  bird = IMG_LoadPNG_RW(birdIMG);
  background = IMG_LoadPNG_RW(backgroundIMG);
  camera = IMG_LoadPNG_RW(cameraIMG);

  if (!bird || !background || !camera)
    errorLog("failed at loading PNG", IMG_GetError());

  ////////////////////////////////////////////// B

  /////////////////////////////////////////////////////////////////////////////// C
  // positioning and scaling
  SDL_Rect backgroundSrcRect_main = {0, 0, 500, 400};
  SDL_Rect birdDistRect_main = {30, 80, 40, 30};
  /////////////////////////////////////////////////////////////////////////////// C
  SDL_Rect cameraDistRect_dev = {0, 0, 500, 400};
  SDL_Rect cameraSrcRect_dev = {0, 0, 0, 400};
  SDL_Rect birdDistRect_dev = {30, 80, 40, 30};

  // mainLoop
  int openMain = 1;
  int openDev = 1;
  int speed = 5;
  while (openMain || openDev)
  {
    // event hundling
    closeEvent(&mainWindow, &devWindow, &openMain, &openDev);

    // main window
    if (openMain)
    {
      /////////////////////////////////////////////////////////////////////////////// C
      // logic
      backgroundSrcRect_main.x += speed;
      if (backgroundSrcRect_main.x > 2000)
        backgroundSrcRect_main.x = 0;
      /////////////////////////////////////////////////////////////////////////////// C

      /////////////////////////////////////////////////////////////////////////////// D
      // draw
      int blitBackground = SDL_BlitSurface(background, &backgroundSrcRect_main, mainScreen, NULL);
      int blitBird = SDL_BlitScaled(bird, NULL, mainScreen, &birdDistRect_main);

      if (blitBird != 0 || blitBackground != 0)
        errorLog("failed at blitSurface", SDL_GetError());

      SDL_UpdateWindowSurface(mainWindow);
      /////////////////////////////////////////////////////////////////////////////// D
    }

    // dev window
    if (openDev)
    {
      // logic
      int camTransition = 0;
      cameraDistRect_dev.x += speed;
      if (cameraDistRect_dev.x > 2000)
        cameraDistRect_dev.x = 0;

      if (cameraDistRect_dev.x > 2000 - 500)
      {
        camTransition = 1;
        cameraSrcRect_dev.x = 2000 - cameraDistRect_dev.x;
        cameraSrcRect_dev.w = 500 - (2000 - cameraDistRect_dev.x);
      }

      birdDistRect_dev.x += speed;
      if (birdDistRect_dev.x > 2000)
      {
        birdDistRect_dev.x = 0;
        birdDistRect_dev.w = 40;
      }

      // draw
      int blitBackground = SDL_BlitSurface(background, NULL, devScreen, NULL);
      // int blitBird = SDL_BlitScaled(bird, NULL, devScreen, &birdDistRect_dev); // not needed for explenation
      int blitCamera = SDL_BlitSurface(camera, NULL, devScreen, &cameraDistRect_dev);
      int blitCamTransition = 0;

      if (camTransition)
        blitCamTransition = SDL_BlitSurface(camera, &cameraSrcRect_dev, devScreen, NULL);

      if (blitCamera != 0 || blitBackground != 0 || /*blitBird != 0 ||*/ blitCamTransition != 0)
        errorLog("failed at blitSurface", SDL_GetError());

      SDL_UpdateWindowSurface(devWindow);
    }

    // temporary to not burn the CPU
    SDL_Delay(1);
  }

  cleanUp(); // A

  return 0;
}