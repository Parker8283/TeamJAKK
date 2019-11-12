#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Control.h>
#include <System.h>

void LoadPlayerControls(void);
void SetControlContext(GameState state);
void UpdatePlayer(void);

GLuint GetPlayerSpriteID(void);

glm::vec3 GetPlayerPos(void);
glm::vec2 GetPlayerMoveDir(void);
float GetPlayerWalkSpeed(void);
#endif
