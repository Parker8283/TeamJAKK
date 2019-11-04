#ifndef SWORD_H
#define SWORD_H

#include <entity.h>
#include "projectile.h"
#include "player.h"
#include "enemy.h"
#include <Controller.h>
#include <Graphics.h>
#include <GameMath.h>

class Sword : public Projectile {

private:

public:
	Player* player;
	double damage;

	typedef enum class State
	{
		Held, 
		Fly, 
		Ground
	} State;

	State currentState;

	Sword(const char*);

	void Init();
	void Update(void);
	void HitEnemy(Enemy e);
	void Pickup();
	void Throw();
	void UpdateState(State);

	State GetState(void);
};

#endif // !SWORD_H
