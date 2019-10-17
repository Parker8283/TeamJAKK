#ifndef SYSTEM_H
#define SYSTEM_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef enum GameState {
  MAIN_MENU = 0,
  RUN_GAME,
  EXIT_GAME
} GameState;

typedef struct FrameTime {
    float currentTime;
    float lastTime;
    float deltaTime;
} FrameTime;

float GetFrameDeltaTime(void);
float GetFrameLastTime(void);
float GetFrameCurrentTime(void);

FrameTime GetFrameTime(void);

GameState GetGameState(void);

void RefreshSystemTimer(void);
void SetGameState(GameState state);
void SystemInit(void);
void UpdateSystemTimer(void);

#endif
