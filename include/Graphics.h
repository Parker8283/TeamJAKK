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

void SetupGraphics(void);
void SetView(glm::mat4 view);

glm::mat4 GetView(void);
glm::mat4 GetProjection(void);

void SetPlayerCurrentFrame(GLuint);

GLuint GetHitShader(void);
GLuint GetHitVAO(void);
GLuint GetHitVBO(void);

GLuint GetShader(void);
GLuint GetPlayerVAO(void);
GLuint GetWallTextureID(void);
GLuint GetFloorTextureID(void);
GLuint GetTileVAO(void);

#endif
