#ifndef SWORD_H
#define SWORD_H

#include <entity.h>
#include "projectile.h"
//#include <enemy.h>
#include <Controller.h>
#include <Graphics.h>
#include <GameMath.h>
#include <list>
//#include <GameRunner.h>

class Sword : public Projectile {
public:
	typedef enum class State
	{
		Held, 
		Fly, 
		Ground
	} State;

	State currentState;

	double damage;

	Sword(const char*);

	void Init();
	void Update(void);
	void Pickup();
	void UpdateState(State);

	
	State GetState(void);
};


void Throw(void*);
#endif // !SWORD_H
