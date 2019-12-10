#include <Controller.h>
#include <Graphics.h>
#include <FileLoader.h>
#include <glm/gtc/matrix_transform.hpp>
#include <stdio.h>
#include <Texture.h>
#include <WindowManager.h>
#include <stb_image.h>

using namespace glm;

static int xRes, yRes;

static GLuint currentPlayerTex;

static const mat2 rot = {
  -1,  0,
  0, -1
};

static mat4 P;
static mat4 V;

//Player VAO and VBOs
static GLuint playerVAO;
static GLuint playerVBOs[2];
static GLuint hitBoxVAO;
static GLuint hitBoxVBO;

static GLuint tileVAO;
static GLuint tileVBOs[2];
static GLuint wallTexture;
static GLuint floorTexture;

static GLuint playerTexture;
static GLuint playerTextureBack;

static GLuint boxProgramID;
static GLuint hitBoxProgramID;

static float playerVerts[18] {
  -1, -1, 0,
  -1,  1, 0,
  1,  -1, 0,
  -1,  1, 0,
  1,  1, 0,
  1, -1, 0
};

static float playerUVs[12] {
  0, 0,
  0, 1,
  1, 0,
  0, 1,
  1, 1,
  1, 0
};

static float tileVerts[18] {
  -.5f, -.5f, 0,
  -.5f,  .5f, 0,
  .5f, -.5f, 0,
  -.5f,  .5f, 0,
  .5f,  .5f, 0,
  .5f, -.5f, 0
};

static void loadCursor() {
  int width, height, n;
  unsigned char* pixels = stbi_load("common/sprites/Cursor32.png", &width, &height, &n, 4);


  GLFWimage image;
  image.width = width;
  image.height = height;
  image.pixels = pixels;

  GLFWcursor* cursor = glfwCreateCursor(&image, 12, 12);
  glfwSetCursor(GetWindow(), cursor);
  glfwSetCursorPos(GetWindow(), 960, 540);
}

void SetPlayerCurrentFrame(GLuint newFrame)
{
	currentPlayerTex = newFrame;
}

void SetupGraphics(void) {
  glfwGetFramebufferSize(GetWindow(), &xRes, &yRes);

  //Construct projection matrix and forget about its existance
  P = perspective(radians(60.0f), (float) xRes / (float) yRes, .1f, 100.0f);

  //Setup box shader program and player texture
  boxProgramID = LoadShader("shaders/BoxShader.vert", "shaders/BoxShader.frag");

  playerTexture     = LoadTexture("common/sprites/GungeonRipoffBase.png");
  playerTextureBack = LoadTexture("common/sprites/GungeonRipoffBaseBack.png");

  wallTexture       = LoadTexture("common/sprites/SingleWall.png");
  floorTexture      = LoadTexture("common/sprites/ground.png");
  hitBoxProgramID   = LoadShader("shaders/HitBoxShader.vert", "shaders/HitBoxShader.frag");

  loadCursor();

  //Setup Player program vert/uv buffer streams
  glGenVertexArrays(1, &playerVAO);
  glBindVertexArray(playerVAO);

  glGenBuffers(2, playerVBOs);
  glBindBuffer(GL_ARRAY_BUFFER, playerVBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(playerVerts), playerVerts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, playerVBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(playerUVs), playerUVs, GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  //Setup Tile program vert/uv buffer streams
  glGenVertexArrays(1, &tileVAO);
  glBindVertexArray(tileVAO);
  
  glGenBuffers(2, tileVBOs);
  glBindBuffer(GL_ARRAY_BUFFER, tileVBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(tileVerts), tileVerts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

  glBindBuffer(GL_ARRAY_BUFFER, tileVBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(playerUVs), playerUVs, GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glGenVertexArrays(1, &hitBoxVAO);
  glBindVertexArray(hitBoxVAO);

  glGenBuffers(1, &hitBoxVBO);
  glBindBuffer(GL_ARRAY_BUFFER, hitBoxVBO);
  glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(vec2), NULL, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);
}

void SetView(mat4 view) {
  V = view;
}

mat4 GetView()
{
  return V;
}

mat4 GetProjection()
{
  return P;
}

GLuint GetHitShader() {
  return hitBoxProgramID;
}

GLuint GetHitVAO() {
  return hitBoxVAO;
}

GLuint GetHitVBO() {
  return hitBoxVBO;
}

GLuint GetShader()
{
  return boxProgramID;
}

GLuint GetPlayerVAO(void) {
  return playerVAO;
}

GLuint GetTileVAO(void) {
  return tileVAO;
}

GLuint GetWallTextureID(void) {
  return wallTexture;
}

GLuint GetFloorTextureID(void) {
  return floorTexture;
}

