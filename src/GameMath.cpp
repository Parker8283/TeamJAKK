#include <GameMath.h>

using namespace glm;

#define PI 3.14159265

// Takes a vector and normalizes it to a scale of -1 to 1
vec2 normalizeDir(vec2 p) {
  float mag = sqrt(p.x*p.x + p.y*p.y);

  if (mag < .00001f && mag > -.00001f)
    return p;

  return vec2(p.x / mag, p.y / mag);
}

vec3 swordMath() {

	//converting mouse x and y coordinates to world coordinates
	double xpos, ypos;
	glfwGetCursorPos(GetWindow(), &xpos, &ypos);
	//printf("Mouse coord: %f %f\n", xpos, ypos);

	vec2 playerPosition;
	playerPosition.x = GetPlayerPos().x;
	playerPosition.y = GetPlayerPos().y;

	double ndcX = (xpos - (1920 / 2)) / (1920 / 2);
	double ndcY = (ypos - (1080 / 2)) / (1080 / 2);
	vec2 ndc = normalizeDir(vec2(ndcX, ndcY));
	vec4 mouseView = inverse(GetP()) * vec4(ndc.x, ndc.y, 0, 1);
	vec4 mouseWorld = inverse(GetView()) * vec4(mouseView.x, mouseView.y, 0, 1);

	vec2 mouseDir = playerPosition - vec2(mouseWorld.x, mouseWorld.y);
	mouseDir      = normalizeDir(mouseDir);

	//printf("Mouse coord: %f %f\n", ndc.x, ndc.y);
	//printf("Player coord: %f %f\n", playerPosition.x, playerPosition.y);
	
	vec2 direction;
	direction.y = ndc.y;
	direction.x = ndc.x;
	

	//First side
	float sideOne = distance(playerPosition.x, playerPosition.y, mouseWorld.x, mouseWorld.y);
	//second side
	float sideTwo = distance(mouseWorld.x, mouseWorld.y, mouseWorld.x, playerPosition.y);

	//angle sword needs to be at to appear to follow the cursor
	//double angle = atan(sideTwo / sideOne);
	float angle = atan2(mouseDir.y, mouseDir.x);
	angle = (angle >= 0 ? angle : (2 * PI + angle));
	angle = angle * 180 / PI;
	
	//printf("angle: %f\n", angle);

	return vec3(-mouseDir.x, mouseDir.y, radians(angle));
}

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
