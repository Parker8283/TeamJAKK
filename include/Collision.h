#ifndef COLLISION_H
#define COLLISION_H

#include <glm/glm.hpp>

class CollisionBox
{
  glm::vec2 pos;

public:
  float x;
  float y;

  CollisionBox(void);
  CollisionBox(float width, float height, glm::vec2 p);
   glm::vec2 GetPos(void);
   void SetPos(glm::vec2);
};

bool checkCollision(CollisionBox box1, CollisionBox box2);

#endif
