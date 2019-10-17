#include <GameMath.h>

using namespace glm;

vec2 normalizeDir(vec2 p) {
  float mag = sqrt(p.x*p.x + p.y*p.y);

  if (mag < .00001f && mag > -.00001f)
    return p;

  return vec2(p.x / mag, p.y / mag);
}
