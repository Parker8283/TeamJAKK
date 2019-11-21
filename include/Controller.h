#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Control.h>
#include <System.h>
#include <Collision.h>
//#include <sword.h>

void LoadPlayerControls(void);
void SetControlContext(GameState state);
void UpdatePlayer(void);
void UpdateKeys(void);
void UnpressKeys(void);

GLuint GetPlayerSpriteID(void);

glm::vec3 GetPlayerPos(void);
glm::vec2 GetPlayerMoveDir(void);
glm::vec2 GetPlayerMoveDir(void);
float GetPlayerWalkSpeed(void);
#endif
