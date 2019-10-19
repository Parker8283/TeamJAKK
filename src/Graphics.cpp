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

static GLuint textureProgramID;

static const mat2 rot = { 
  -1,  0,
   0, -1
 };

static mat4 P;
static mat4 V;

//Player VAO and VBOs
static GLuint playerVAO;
static GLuint playerVBOs[2];

static GLuint playerTexture;
static GLuint playerTextureBack;
static GLuint boxProgramID;
static GLuint boxMVPID;
static GLuint boxRotID;
static GLuint boxTexID;

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

void DrawPlayer(void) {
  mat4 M   = translate(mat4(1), GetPlayerPos());
  //printf("%.2f %.2f %.2f %.2f\n", M[0][0], M[1][0], M[2][0], M[3][0]);
  //printf("%.2f %.2f %.2f %.2f\n", M[0][1], M[1][1], M[2][1], M[3][1]);
  //printf("%.2f %.2f %.2f %.2f\n", M[0][2], M[1][2], M[2][2], M[3][2]);
  //printf("%.2f %.2f %.2f %.2f\n", M[0][3], M[1][3], M[2][3], M[3][3]);
  mat4 MVP = P * V * M;
  //printf("%.2f %.2f %.2f %.2f\n", MVP[0][0], MVP[1][0], MVP[2][0], MVP[3][0]);
  //printf("%.2f %.2f %.2f %.2f\n", MVP[0][1], MVP[1][1], MVP[2][1], MVP[3][1]);
  //printf("%.2f %.2f %.2f %.2f\n", MVP[0][2], MVP[1][2], MVP[2][2], MVP[3][2]);
  //printf("%.2f %.2f %.2f %.2f\n\n", MVP[0][3], MVP[1][3], MVP[2][3], MVP[3][3]);
  //exit(1);

  glBindVertexArray(playerVAO);
  glUseProgram(boxProgramID);

  glActiveTexture(GL_TEXTURE0);

  double xPos, yPos;
  glfwGetCursorPos(GetWindow(), &xPos, &yPos);
  // glBindTexture(GL_TEXTURE_2D, NULL);
   printf("%.2f %.2f\n", yPos, GetPlayerPos().y);
  if (yPos < GetPlayerPos().y) {
    glBindTexture(GL_TEXTURE_2D, playerTextureBack);
  } else {
    glBindTexture(GL_TEXTURE_2D, playerTexture);
  }

  glUniform1i(boxTexID, 0);

  glUniformMatrix2fv(boxRotID, 1, GL_FALSE, &rot[0][0]);
  glUniformMatrix4fv(boxMVPID, 1, GL_FALSE, &MVP[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void SetupGraphics(void) {
  glfwGetFramebufferSize(GetWindow(), &xRes, &yRes);

  //Construct projection matrix and forget about its existance
  P = perspective(radians(60.0f), (float) xRes / (float) yRes, .1f, 100.0f);

  //Setup box shader program and player texture
  boxProgramID = LoadShader("shaders/BoxShader.vert", "shaders/BoxShader.frag");
  boxMVPID     = glGetUniformLocation(boxProgramID, "MVP");
  boxTexID     = glGetUniformLocation(boxProgramID, "tex");
  boxRotID     = glGetUniformLocation(boxProgramID, "uvRot");

  playerTexture = LoadTexture("common/sprites/GungeonRipoffBase.png");
  playerTextureBack = LoadTexture("common/sprites/GungeonRipoffBaseBack.png");

  LoadCursor();

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
}

void SetView(mat4 view) {
  V = view;
}

GLuint GetPlayerVAO(void) {
  return playerVAO;
}


void LoadCursor() {
  int width, height, n;
  unsigned char* pixels = stbi_load("common/sprites/Cursor32.png", &width, &height, &n, 4);

  GLFWimage image;
  image.width = width;
  image.height = height;
  image.pixels = pixels;

  GLFWcursor* cursor = glfwCreateCursor(&image, 12, 12);
  glfwSetCursor(GetWindow(), cursor);
}