#include <FileLoader.h>
#include <GameRunner.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Graphics.h>
#include <math.h>
#include <stdio.h>
#include <System.h>
#include <WindowManager.h>

#define XRES 1920
#define YRES 1080

int main(void) {

  CreateWindow();         //Setup GLFW window and intitialize it
  SystemInit();           //Initialize game timer and game state
  SetupGraphics();        //Setup shader programs with shader variable locations
  SetGameState(RUN_GAME); //Set the game into a run game state for demoing right now

  while(GetGameState() != EXIT_GAME) {
    switch(GetGameState()) {
      case MAIN_MENU:
        //Do something here
        break;
      case RUN_GAME:
        EnterGameLoop();  // Enter game loop
        break;
      case EXIT_GAME:
        break;
    }
  }

  return 0;
}
