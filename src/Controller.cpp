#include <Control.h>
#include <Controller.h>
#include <GameMath.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Graphics.h>
#include <map>
#include <System.h>
#include <WindowManager.h>

using namespace glm;

static const float playerWalkSpeed = 5.0f;

static GLuint  playerSpriteID;

static vec2 moveDir;
static vec2 playerPos;

static std::map<int, bool> pressedMap;

static const vec3 UP = vec3(0, 1, 0);

static void player_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (action == GLFW_RELEASE) {
    pressedMap[key] = false;
    return;
  } else if (action == GLFW_PRESS) {
    pressedMap.insert(std::pair<int, bool>(key, true));
    return;
  }
}

static void player_mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
  if (action == GLFW_RELEASE) {
    pressedMap[button + MOUSE_OFFSET] = false;
    return;
  } else if (action == GLFW_PRESS) {
    pressedMap.insert(std::pair<int, bool>(button + MOUSE_OFFSET, true));
  }
}

static void moveUp(void* null) {
  moveDir.y += 1.0f;
}

static void moveLeft(void* null) {
  moveDir.x -= 1.0f;
}

static void moveDown(void* null) {
  moveDir.y -= 1.0f;
}

static void moveRight(void* null) {
  moveDir.x += 1.0f;
}

static void exitGame(void* null) {
  SetGameState(GameState::EXIT_GAME);
}

void LoadPlayerControls(void) {
  BindKey(GLFW_KEY_W,      moveUp,    NULL, NULL);
  BindKey(GLFW_KEY_A,      moveLeft,  NULL, NULL);
  BindKey(GLFW_KEY_S,      moveDown,  NULL, NULL);
  BindKey(GLFW_KEY_D,      moveRight, NULL, NULL);
  BindKey(GLFW_KEY_ESCAPE, exitGame,  NULL, NULL);
}

void SetControlContext(GameState state) {
  switch (state) {
  case GameState::RUN_GAME:
    glfwSetKeyCallback(GetWindow(), player_key_callback);
    glfwSetMouseButtonCallback(GetWindow(), player_mouse_callback);
    break;
  default:
    glfwSetKeyCallback(GetWindow(), NULL);
    glfwSetMouseButtonCallback(GetWindow(), NULL);
  }
}

void UpdatePlayer(void) {
  float frameDelta = GetFrameDeltaTime();
  //Reset move direction
  moveDir = vec2(0);
  /* Check all keyboard keys */
  for (std::map<int, bool>::iterator it = pressedMap.begin(); it != pressedMap.end(); it++) {
    if (it->second) {
      ActivateKey(it->first);
    } else {
      DeActivateKey(it->first);
      pressedMap.erase(it->first);
    }
  }

  moveDir    = normalizeDir(moveDir);
  playerPos += moveDir * frameDelta * playerWalkSpeed;
  //SetView(lookAt(vec3(0, 0, 10), vec3(0, 0, 0), UP));
  SetView(lookAt(vec3(playerPos.x, playerPos.y, 10), vec3(playerPos.x, playerPos.y, 0), UP));
}

GLuint GetPlayerSpriteID(void) {
  return playerSpriteID;
}

vec3 GetPlayerPos(void) {
  return vec3(playerPos, 0);
}
