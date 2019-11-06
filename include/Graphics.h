#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Controller.h>
#include <Graphics.h>
#include <FileLoader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <Texture.h>
#include <WindowManager.h>
#include <stb_image.h>

void DrawPlayer(void);
void SetupGraphics(void);
void SetView(glm::mat4 view);
void LoadCursor();

glm::mat4 GetView();
glm::mat4 GetProjection();

GLuint GetShader();

void SetPlayerCurrentFrame(GLuint);

GLuint GetShader();
GLuint GetPlayerVAO(void);
GLuint GetWallTextureID(void);
GLuint GetFloorTextureID(void);
GLuint GetTileVAO(void);

#endif
