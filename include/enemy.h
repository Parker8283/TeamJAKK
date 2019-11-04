#ifndef ENEMY_H
#define ENEMY_H

#include <entity.h>
#include <player.h>
#include <projectile.h>

class Enemy : Entity {

private:

public:
	typedef enum class BehaviorState
	{
		Seek, 
		Fire, 
		Flee
	} BehaviorState;

	int health;
	
	float moveSpeed;

	double timer=0;
	double damage;
	
	GLuint weapon;
	
	glm::vec2 target;
	glm::vec2 moveTarget;
	
	Projectile* shot;
	
	BehaviorState currentState;

	Enemy(glm::vec2 pos, const char*);

	void Update();
	void Draw();
	void UpdateState(BehaviorState s);
	void Attack();
	void Die();
	BehaviorState GetState();
	void SetState(BehaviorState);

};

#endif // !ENEMY_H
