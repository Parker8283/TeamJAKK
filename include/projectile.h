#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <entity.h>

class Projectile : public Entity {

public:
	float speed;
	glm::vec2 direction;
	bool HitEnemy;
	bool doesExist;

	Projectile(char*);
	void Init(glm::vec2, glm::vec2);
	void Update();
	glm::vec2 GetDirection();
	void UpdateSpeed(double s);
	void collide();

};

#endif // !PROJECTILE_H