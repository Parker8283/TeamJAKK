#include <Collision.h>
#include <glm/glm.hpp>
#include <Graphics.h>

using namespace glm;

CollisionBox::CollisionBox(void) {
  x = 1;
  y = 1;
  this->pos = NULL;
}

CollisionBox::CollisionBox(float width, float height, vec2* p) {
  x = width;
  y = height;
  this->pos = p;
}

 vec2 CollisionBox::GetPos(void) {
  return *this->pos;
}

void CollisionBox::Draw(void) {
  float x0 = pos->x - x / 2.0f;
  float x1 = x0 + x;
  float y0 = pos->y - y / 2.0f;
  float y1 = y0 + y;

  float verts[] = {
    x0, y0, x1, y0,
    x1, y0, x1, y1,
    x1, y1, x0, y1,
    x0, y1, x0, y0
  };

  glLineWidth(20.0f);

  glUseProgram(GetHitShader());
  glBindVertexArray(GetHitVAO());
  glBindBuffer(GL_ARRAY_BUFFER, GetHitVBO());
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

  mat4 MVP = GetProjection() * GetView();
  glUniformMatrix4fv(glGetUniformLocation(GetHitShader(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

  glDrawArrays(GL_LINES, 0, 8);
}

bool checkCollision(CollisionBox box1, CollisionBox box2) {
	//printf("%f %f\n", box1.GetPos().x, box1.GetPos().y);
  float b1x0 = box1.GetPos().x - box1.x / 2;
  float b1x1 = b1x0 + box1.x;
  float b1y0 = box1.GetPos().y - box1.y / 2;
  float b1y1 = b1y0 + box1.y;

  float b2x0 = box2.GetPos().x - box2.x / 2;
  float b2x1 = b2x0 + box2.x;
  float b2y0 = box2.GetPos().y - box2.y / 2;
  float b2y1 = b2y0 + box2.y;

  //Checks all sides of box to check collision
  if (b1x0 < b2x1 && b1x1 > b2x0 &&
      b1y0 < b2y1 && b1y1 > b2y0)
    return true;

  return false;
}
