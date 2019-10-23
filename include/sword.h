#ifndef SWORD_H
#define SWORD_H

#include <entity.h>
#include "projectile.h"
#include "player.h"
#include "enemy.h"

class Sword {

private:

public:
	Player player;
	double damage;

	typedef enum State
	{
		Held, 
		Fly, 
		Ground
	};
	State currentState;

	void HitEnemy(Enemy e);
	void Pickup();
	void Throw();

};


#endif // !SWORD_H