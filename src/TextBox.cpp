#include <ft2build.h>
#include FT_FREETYPE_H

#include <FileLoader.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>
#include <TextBox.h>
#include <WindowManager.h>

using namespace glm;

static FT_Library library;
static FT_Face    face;

static GLuint textProgram;
static GLuint brightnessID;
static GLuint colorID;
static GLuint textureID;

static GLuint filledProgram;
static GLuint filledColorID;
static GLuint filledBrightnessID;

static GLuint VAO, VBO;
static GLuint texture;

typedef struct Character {
  GLuint tex;
  glm::ivec2 size;
  glm::ivec2 bearing;
  long int advance;
} Character;

std::map<GLchar, Character> CharacterMap;

void SetupText(void) {
  //Setup Graphics
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_STATIC_DRAW); //Allocate Size in memory

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

  textProgram  = LoadShader("../../shaders/TextShader.vert", "../../shaders/TextShader.frag");
  brightnessID = glGetUniformLocation(textProgram, "textBrightness");
  colorID      = glGetUniformLocation(textProgram, "textColor");
  textureID    = glGetUniformLocation(textProgram, "tex");

  if (FT_Init_FreeType(&library) != FT_Err_Ok)
  {
    printf("Failed to initialize Text Texture\n");
  }

  if (FT_New_Face( library, "../../common/fonts/Raleway-Black.ttf", 0, &face) != FT_Err_Ok) {
    printf("Failed to create font face for Text Rendering\n");
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  for (GLubyte ch = 0; ch < 128; ch++) {
    if (FT_Load_Char(face, ch, FT_LOAD_RENDER)) {
      fprintf(stderr, "Error: FreeType: Failed to load glyph character %c\n", (char) ch);
      continue;
    }

    // Generate texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Now store character for later use
    Character character = {
      texture,
      glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
      glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
      face->glyph->advance.x
    };
    CharacterMap.insert(std::pair<GLchar, Character>(ch, character));
  }

  FT_Done_Face(face);
  FT_Done_FreeType(library);

  //Setup Filled Box Graphics
  filledProgram      = LoadShader("../../shaders/FillShader.vert", "../../shaders/FillShader.frag");
  filledBrightnessID = glGetUniformLocation(filledProgram, "brightness");
  filledColorID      = glGetUniformLocation(filledProgram, "color");


}

TextBox::TextBox(const char* s, glm::vec4 p) {
  pos = p;
  SetText(s);
}

void TextBox::Draw(void) {
  //Middle Alignment
  float xlen  = 0.0f;
  float ysize = 0.0f;

  vec2 res = GetWindowResolution();
  for (uint i = 0; i < strlen(buf); i++) {
    Character ch = CharacterMap[buf[i]];
    xlen += ((ch.advance >> 6) * scale) / res.x;
    if (((ch.size.y + ch.bearing.y) * scale) > ysize)
      ysize = ((ch.size.y + ch.bearing.y) * scale) / res.y;
  }

  float x  = (pos.x + pos.z) * 0.5f;
  float y  = (pos.y + pos.w) * 0.5f;

  x -= xlen / 2.0f;
  y -= ysize / 4.0f;

  GLfloat xTemp = x;

  for (uint i = 0; i < strlen(buf); i++) {
    Character ch = CharacterMap[buf[i]];
    if (buf[i] == '\n') {
      y -= ((ch.advance >> 6) * scale * 2.0f) / res.y;
      x = xTemp;
      continue;
    }

    float xpos = x + (ch.bearing.x * scale) / res.x;
    float ypos = y - ((ch.size.y - ch.bearing.y) * scale) / res.y;

    float w = (ch.size.x * scale) / res.x;
    float h = (ch.size.y * scale) / res.y;

    // Update VBO for each character
    float verts[] = {
      xpos,     ypos + h,   0.0f, 0.0f,
      xpos,     ypos,       0.0f, 1.0f,
      xpos + w, ypos,       1.0f, 1.0f,

      xpos,     ypos + h,   0.0f, 0.0f,
      xpos + w, ypos,       1.0f, 1.0f,
      xpos + w, ypos + h,   1.0f, 0.0f
    };

    glUseProgram(textProgram);
    glBindVertexArray(VAO);

    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ch.tex);

    glUniform1i(textureID, 0);
    glUniform1f(brightnessID, brightness);
    glUniform3f(colorID, color.x, color.y, color.z);

    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6 * 4, verts);

    // Render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += ((ch.advance >> 6) * scale) / res.x; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }
}

void TextBox::SetBrightness(float b) {
  brightness = b;
}

void TextBox::SetColor(vec3 col) {
  color = col;
}

void TextBox::SetScale(float s) {
  scale = s;
}

void TextBox::SetText(const char* text) {
  memset(buf, 0, sizeof(buf));
  strncpy(buf, text, 256);
}

FilledBox::FilledBox(vec4 p, vec3 col) {
  pos   = p;
  color = col;
}

void FilledBox::Draw(void) {
  float verts[] = {
    pos.x, pos.y, 0, 0,
    pos.z, pos.y, 0, 0,
    pos.x, pos.w, 0, 0, 

    pos.z, pos.y, 0, 0,
    pos.z, pos.w, 0, 0,
    pos.x, pos.w, 0, 0
  };

  glUseProgram(filledProgram);
  glBindVertexArray(VAO);

  glUniform1f(filledBrightnessID, brightness);
  glUniform3f(filledColorID, color.x, color.y, color.z);

  // Update content of VBO memory
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6 * 4, verts);

  // Render quad
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void FilledBox::SetBrightness(float b) {
  brightness = b;
}

void FilledBox::SetColor(vec3 col) {
  color = col;
}

void FilledBox::SetPos(vec4 p) {
  pos = p;
}

