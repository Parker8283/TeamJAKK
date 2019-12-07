#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <behaviors.h>
#include <DungeonMap.h>
#include <DungeonTile.h>
#include <GameMath.h>

#include <cstdlib>
#include <ctime>
#include <vector>


class Archetype {
public:
	bool doesShoot;

	char shotTexture[64];
	char enemyTexture[64];

	int health;
	int radius;
	
	float damage; 
	float moveSpeed;
	float shotSpeed;
	float shotFrequency;
	
	Behavior::AIType behavior;
	glm::vec2 size;
	glm::vec2 shotSize;

	int score;

	Archetype(const char*, const char*, bool, float, float, float, int, float, int, Behavior::AIType, glm::vec2, glm::vec2, int score);
};

void GenerateEnemyRoom(std::vector<DungeonTile>);
void GenerateEnemyRoom(DungeonTile*, int);
// args		enemy texture, shot texture, doesShoot, moveSpeed, shotFrequency, AIType, 
void GenerateEnemy(glm::vec2, char*, char*, bool, float, float, float, int, float, int, Behavior::AIType, glm::vec2, glm::vec2, int score);
void GenerateEnemy(glm::vec2, Archetype);

glm::vec2 GetRandomPos(glm::vec2, glm::vec2);

#endif // !ENEMY_MANAGER_H
