#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <entity.h>

class Projectile : public Entity {

public:
	glm::vec2 direction;
	bool HitEnemy;
	float damage;

	//Projectile(const char*);
	Projectile(const char*, glm::vec2, glm::vec2, float, glm::vec2);
	~Projectile(void);

	void Init(glm::vec2, glm::vec2);
	void Update();
	glm::vec2 GetDirection();
	void UpdateSpeed(double s);
	void collide(void);

};

#endif // !PROJECTILE_H
