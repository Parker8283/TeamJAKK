#ifndef ENEMY_H
#define ENEMY_H

#include <entity.h>
#include <player.h>
#include <projectile.h>
#include <GameMath.h>
#include <behaviors.h>

class Enemy : Entity {

private:

public:
	typedef enum class BehaviorState
	{
		Seek, 
		Fire, 
		Flee, 
		Fleeing
	} BehaviorState;

	int health;
	
	float moveSpeed;

	double timer=0;
	double damage;
	
	GLuint weapon;
	
	glm::vec2 target;
	glm::vec2 moveTarget;
	glm::vec2 moveDir;

	Projectile* shot;
	Behavior* behavior;
	
	BehaviorState behaviorState;

	Enemy(glm::vec2 pos, const char*);
	Enemy(glm::vec2 pos, const char*, Behavior::AIType);

	void Update();
	void Draw();
	void UpdateState(BehaviorState s);
	void Attack();
	void Die();
	BehaviorState GetState();
	void SetState(BehaviorState);

};

#endif // !ENEMY_H
