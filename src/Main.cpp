#include <FileLoader.h>
#include <GameRunner.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Graphics.h>
#include <MainMenu.h>
#include <math.h>
#include <stdio.h>
#include <System.h>
#include <TextBox.h>
#include <WindowManager.h>

#define XRES 1920
#define YRES 1080

int main(void) {

  CreateWindow();         //Setup GLFW window and intitialize it
  SystemInit();           //Initialize game timer and game state
  SetupGraphics();        //Setup shader programs with shader variable locations
  SetupText();            //Setup text rendering programs
  SetGameState(GameState::MAIN_MENU); //Set the game into a run game state for demoing right now

  while(GetGameState() != GameState::EXIT_GAME) {
    switch(GetGameState()) {
	case GameState::MAIN_MENU:
        MainMenu();
        break;
	case GameState::RUN_GAME:
        EnterGameLoop();  // Enter game loop
        break;
	case GameState::EXIT_GAME:
        break;
    }
  }

  return 0;
}
