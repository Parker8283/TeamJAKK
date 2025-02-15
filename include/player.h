#ifndef PLAYER_H
#define PLAYER_H

#include <entity.h>
#include <enemy.h>
#include <list>
#include <sword.h>

class Player : public Entity {
	Sword* heldSword;

public:
	GLuint front, back, invinc;
	bool hasSword;
	int curHealth;
	int maxHealth;
	float invincTimer;
	
	uint score;
	
	Player();

	bool Update();

	void AddScore(uint s);
	uint GetScore();
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
