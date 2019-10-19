#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <GL/glew.h>
#include <glm/glm.hpp>

void DrawPlayer(void);
void SetupGraphics(void);
void SetView(glm::mat4 view);
void LoadCursor();

GLuint GetPlayerVAO(void);
#endif
