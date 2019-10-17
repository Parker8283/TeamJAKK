#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <GL/glew.h>
#include <glm/glm.hpp>

void LoadPlayerControls(void);
void MakeGameRunControlContext(void);
void UpdatePlayer(void);

GLuint GetPlayerSpriteID(void);

glm::vec3 GetPlayerPos(void);
#endif
