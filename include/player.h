#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>

class Player : Entity{

public:
	bool hasSword;
	int health;
	
	void loadControls();
	void GetSword();
	void Attack();
	void Pickup(Entity e);

};


#endif // !PLAYER_H