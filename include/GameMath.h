#ifndef GAME_MATH_H
#define GAME_MATH_H
#include <glm/glm.hpp>
#include <cmath>
#include <Graphics.h>
#include <glm/gtc/matrix_transform.hpp>

glm::vec2 normalizeDir(glm::vec2 p);
glm::vec3 swordMath();
float distance(float, float, float, float);
int quadrant(glm::vec2);

#endif
