#ifndef ENEMY_H
#define ENEMY_H

#include <entity.h>
#include <player.h>
#include <projectile.h>
#include <GameMath.h>
#include <behaviors.h>
#include <enemy_manager.h>

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
	float shotFrequency;
	bool doesShoot;
	bool flipped = false;
	
	float shotSpeed;
	glm::vec2 shotSize;

	float timer=0;
	float damage;
	
	char* weaponFile;
	
	glm::vec2 target;
	glm::vec2 moveTarget;
	glm::vec2 moveDir;

	Projectile* shot;
	Behavior* behavior;
	
	BehaviorState behaviorState;

	//Enemy(glm::vec2 pos, const char*);
	Enemy(glm::vec2 pos, const char*, Behavior::AIType);
	Enemy(glm::vec2 pos, Archetype);

	void Update();
	void Draw();
	void UpdateState(BehaviorState s);
	void Attack();
	void TakeDamage(int damage);
	void Die();
	BehaviorState GetState();
	void SetState(BehaviorState);

};

#endif // !ENEMY_H
