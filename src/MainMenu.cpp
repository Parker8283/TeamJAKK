#include <algorithm>
#include <MainMenu.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <System.h>
#include <TextBox.h>
#include <WindowManager.h>

using namespace glm;

static bool loop  = 1;

static int cursor = 0;
static float brightness[2] = { 1.0f, .5f };


static void decrementCursor(void) {
  brightness[cursor] = .5f;
  cursor--;
  cursor = std::min(std::max(cursor, 0), 1); //range from [0 to 1]
  brightness[cursor] = 1.0f;
}

static void incrementCursor(void) {
  brightness[cursor] = .5f;
  cursor++;
  cursor = std::min(std::max(cursor, 0), 1); //range from [0 to 1]
  brightness[cursor] = 1.0f;
}

static void enter(void) {
  switch(cursor) {
    case 0:
      SetGameState(GameState::RUN_GAME);
      break;
    case 1:
      SetGameState(GameState::EXIT_GAME);
  };
  loop = 0;
}

static void mainmenu_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_PRESS) {
    switch (key) {
    case GLFW_KEY_W:
      decrementCursor();
      break;
    case GLFW_KEY_UP:
      decrementCursor();
      break;
    case GLFW_KEY_S:
      incrementCursor();
      break;
    case GLFW_KEY_DOWN:
      incrementCursor();
      break;
    case GLFW_KEY_ENTER:
      enter();
      break;
    };
  }
}

void MainMenu(void) {

  TextBox box1 = TextBox("Start Game", vec4(-.1f, .05f, .1f, .15f));
  TextBox box2 = TextBox("Exit", vec4(-.1f, -.15f, .1f, -.05f));

  glClearColor(0, 0, 0, 1);
  glfwSetKeyCallback(GetWindow(), mainmenu_key_callback);
  while(loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    box1.SetBrightness(brightness[0]);
    box2.SetBrightness(brightness[1]);
    
    box1.Draw();
    box2.Draw();

    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }

  //Disable key call back
  glfwSetKeyCallback(GetWindow(), NULL);
}
