#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include <enemy.h>
#include <list>
#include <sword.h>

class Player : public Entity{

public:
	GLuint front, back;
	bool hasSword;
	int health;
	
	Player();

	void Draw();
	void Update();
	void loadControls();
	Sword* GetSword();
	void Attack(void*);
	void Pickup(Entity e);
	glm::vec3 GetPosition();
	float GetPlayerWalkSpeed();
};


#endif // !PLAYER_H