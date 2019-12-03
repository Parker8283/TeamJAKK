#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include <enemy.h>
#include <list>
#include <sword.h>

class Player : public Entity {
	Sword* heldSword;

public:
	GLuint front, back;
	bool hasSword;
	int curHealth;
	int maxHealth;
	
	uint score;
	
	Player();

	bool Update();

	void Attack(void*);
	void DamagePlayer(int damage);
	void Draw();
	void loadControls();
	void Pickup(Entity e);
	
	int GetHealth(void);
	int GetMaxHealth(void);

	float GetPlayerWalkSpeed();
	
	Sword* GetSword();
	
	glm::vec3 GetPosition();
};


#endif // !PLAYER_H
