#include <System.h>

static FrameTime frameTime;
static GameState system_Game_State;

float GetFrameDeltaTime(void) {
  return frameTime.deltaTime;
}

float GetFrameLastTime(void) {
  return frameTime.lastTime;
}

float GetFrameCurrentTime(void) {
  return frameTime.currentTime;
}

FrameTime GetFrameTime(void) {
  return frameTime;
}

GameState GetGameState(void) {
  return system_Game_State;
}

void RefreshSystemTimer(void) {
  frameTime.lastTime = (float) glfwGetTime();
}

void SetGameState(GameState state) {
  system_Game_State = state;
}

/* Call in Main to start up key game systems */
void SystemInit(void) {
  float glTime = (float) glfwGetTime();

  frameTime.currentTime = glTime;
  frameTime.lastTime    = glTime;
  frameTime.deltaTime   = glTime;

  system_Game_State = MAIN_MENU;
}

void UpdateSystemTimer(void) {
  frameTime.currentTime = (float) glfwGetTime();
  frameTime.deltaTime   = frameTime.currentTime - frameTime.lastTime;
  frameTime.lastTime    = frameTime.currentTime;
}
