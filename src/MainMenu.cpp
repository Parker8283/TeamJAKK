#include <algorithm>
#include <Controller.h>
#include <MainMenu.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <System.h>
#include <TextBox.h>
#include <WindowManager.h>
#include <GameRunner.h>
#include <sstream>
#include <string.h>

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

static void menu_enter(void) {
  switch (cursor) {
  case 0:
    SetGameState(GameState::RUN_GAME);
    break;
  case 1:
    SetGameState(GameState::EXIT_GAME);
  };
  loop = 0;
}

static void pause_enter(void) {
  switch (cursor) {
  case 0:
    SetGameState(GameState::RUN_GAME);
    SetControlContext(GameState::RUN_GAME);
    break;
  case 1:
    SetGameState(GameState::EXIT_GAME);
    break;
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
      menu_enter();
      break;
    case GLFW_KEY_ESCAPE:
      loop = 0;
      break;
    };
  }
}

static void pause_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
      pause_enter();
      break;
    };
  }
}

void MainMenu(void) {
  TextBox box1 = TextBox("Start Game", vec4(-.1f, .05f, .1f, .15f));
  TextBox box2 = TextBox("Exit", vec4(-.1f, -.15f, .1f, -.05f));

  glClearColor(0, 0, 0, 1);
  glfwSetKeyCallback(GetWindow(), mainmenu_key_callback);
  while (loop) {
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

void GameOver(void) {
	char charar[256];
	snprintf(charar, sizeof(charar), "Score: %u", GetPlayer()->GetScore());

  loop = 1;
  TextBox box0  = TextBox("GAME OVER", vec4(-.8f, .75f, .8f, .25f));
  TextBox box05 = TextBox(charar, vec4(-.8f, .35f, .8f, -.05f));
  TextBox box1  = TextBox("Restart Game", vec4(-.1f, -.05f, .1f, -.15f));
  TextBox box2  = TextBox("Exit", vec4(-.1f, -.25f, .1f, -.35f));

  glClearColor(0, 0, 0, 1);
  glfwSetKeyCallback(GetWindow(), mainmenu_key_callback);
  while (loop) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    box1.SetBrightness(brightness[0]);
    box2.SetBrightness(brightness[1]);
    box0.SetBrightness(1.0f);
    box05.SetBrightness(1.0f);

    box0.SetScale(5);
    box05.SetScale(3);
    box0.SetColor(glm::vec3(1, 0, 0));
    box05.SetColor(glm::vec3(.5f, 0, .5f));

    box0.Draw();
    box05.Draw();
    box1.Draw();
    box2.Draw();

    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }

  //Disable key call back
  glfwSetKeyCallback(GetWindow(), NULL);
}

void PauseGame(void) {
  loop = 1;

  FilledBox fill = FilledBox(vec4(-1.0f, -1.0f, 1.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, .025f));
  TextBox box1   = TextBox("Resume Game", vec4(-.1f, .05f, .1f, .15f));
  TextBox box2   = TextBox("Exit Game", vec4(-.1f, -.15f, .1f, -.05f));

  glfwSetKeyCallback(GetWindow(), pause_key_callback);
  while (loop) {
    glClear(GL_DEPTH_BUFFER_BIT);

    box1.SetBrightness(brightness[0]);
    box2.SetBrightness(brightness[1]);

    box1.Draw();
    box2.Draw();
    fill.Draw();

    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }
}
