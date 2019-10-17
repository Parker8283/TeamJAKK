#include <Controller.h>
#include <GameRunner.h>
#include <Graphics.h>
#include <stdio.h>
#include <System.h>
#include <WindowManager.h>

void EnterGameLoop(void) {
  LoadPlayerControls();
  MakeGameRunControlContext();

  glClearColor(0, 0, 0, 1);
  RefreshSystemTimer();
  while (GetGameState() == RUN_GAME) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateSystemTimer();
    UpdatePlayer();

    DrawPlayer();

    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }
}
