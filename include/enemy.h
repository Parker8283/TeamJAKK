#ifndef ENEMY_H
#define ENEMY_H

#include <entity.h>
#include "projectile.h"
#include "player.h"

class Enemy : Entity {

private:

public:

	glm::vec2 target;
	double moveSpeed;
	int health;
	Projectile shot;
	double damage;
	

	typedef enum State
	{
		Seek, 
		Fire, 
		Flee
	};
	State currentState;

	void UpdateState(State s);
	void Attack();
	void Die();

};

#endif // !ENEMY_H