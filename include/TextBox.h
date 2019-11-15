#ifndef TEXT_BOX_H
#define TEXT_BOX_H
#include <glm/glm.hpp>

void SetupText(void);

class TextBox
{
  char buf[256];

  float brightness = 1.0f; //[0, 1] Default of full brightness
  float scale      = 1.0f; //Default of 1:1 scale

  glm::vec3 color = glm::vec3(1); //Default white
  glm::vec4 pos;  //In screen coords

public:
  TextBox(const char* s, glm::vec4 p);
  void Draw(void);
  void SetBrightness(float b);
  void SetColor(glm::vec3 col);
  void SetScale(float s);
  void SetText(const char* text);
};

#endif
