#ifndef PROJECTILE_H
#define PROJECTILE

#include <entity.h>

class Projectile : Entity {

public:
	double speed;
	glm::vec2 direction;
	bool HitEnemy;


	glm::vec2 GetDirection();
	void UpdateSpeed(double s);
	void collide();
};

#endif // !PROJECTILE_H