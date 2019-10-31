#ifndef ENEMY_H
#define ENEMY_H

#include <entity.h>
#include <player.h>
#include <projectile.h>

class Enemy : public Entity {

private:

public:

	glm::vec2 target;
	glm::vec2 moveTarget;
	float moveSpeed;
	int health;
	Projectile* shot;
	double damage;
	GLuint weapon;
	double timer=0;
	

	typedef enum class BehaviorState
	{
		Seek, 
		Fire, 
		Flee
	} BehaviorState;
	BehaviorState currentState;

	Enemy(char*);

	void Init(glm::vec2);
	void Update();
	void Draw();
	void UpdateState(BehaviorState s);
	void Attack();
	void Die();
	BehaviorState GetState();
	void SetState(BehaviorState);

};

#endif // !ENEMY_H