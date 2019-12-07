
#include <Control.h>
#include <Controller.h>
#include <entity.h>
#include <GameRunner.h>
#include <GameMath.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Graphics.h>
#include <list>
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

/**
double timer = 0;
int currentF = 0;
GLuint arrayFrames[4];
static void moveRight(void* null) {
  currentF = 0;
  //glBindTexture(GL_TEXTURE_2D, arrayRight[0]);
  arrayFrames[0] = LoadTexture(ROOT_DIR"/common/sprites/GungeonRipoffFrame1.png");
  arrayFrames[1] = LoadTexture(ROOT_DIR"/common/sprites/GungeonRipoffFrame2.png");
  arrayFrames[2] = LoadTexture(ROOT_DIR"/common/sprites/GungeonRipoffFrame3.png");
  arrayFrames[3] = LoadTexture(ROOT_DIR"/common/sprites/GungeonRipoffFrame4.png");

  moveDir.x += 1.0f;
}

void rightWalkCycle(void) {
  timer += GetFrameDeltaTime();
  if (timer > 0.2f) {
    currentF++;
    timer = 0;
    SetPlayerCurrentFrame( arrayFrames[currentF]);
    if (currentF = 3) {
      currentF = 0;
    }

  }
} */

static void pauseGame(void* null) {
  SetGameState(GameState::PAUSE_GAME);
  pressedMap[GLFW_KEY_ESCAPE] = false;
}

void LoadPlayerControls(void) {
  BindKey(GLFW_KEY_W,      moveUp,    NULL, NULL);
  BindKey(GLFW_KEY_A,      moveLeft,  NULL, NULL);
  BindKey(GLFW_KEY_S,      moveDown,  NULL, NULL);
  BindKey(GLFW_KEY_D,      moveRight, NULL, NULL);
  BindKey(GLFW_KEY_ESCAPE, pauseGame,  NULL, NULL);
  BindMouse(GLFW_MOUSE_BUTTON_1, Throw, NULL, NULL);

  playerPos = vec2(7, 4);
  moveDir = vec2(0, 0);
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

void UpdateKeys(void) {
	//Reset move direction
	moveDir = vec2(0);
	/* Check all keyboard keys */
	for (std::map<int, bool>::iterator it = pressedMap.begin(); it != pressedMap.end(); it++) {
		if (it->second) {
			ActivateKey(it->first);
		}
		else {
			DeActivateKey(it->first);
			pressedMap.erase(it->first);
		}
	}
}

void UnpressKeys(void) {
	moveDir = vec2(0);
	for (std::map<int, bool>::iterator it = pressedMap.begin(); it != pressedMap.end(); it++) {
		DeActivateKey(it->first);
		pressedMap.erase(it->first);
	}
}

GLuint GetPlayerSpriteID(void) {
  return playerSpriteID;
}

vec2 GetPlayerMoveDir(void)
{
	return moveDir;
}

vec3 GetPlayerPos(void) {
  return vec3(playerPos, 0);
}

float GetPlayerWalkSpeed(void)
{
	return playerWalkSpeed;
}
