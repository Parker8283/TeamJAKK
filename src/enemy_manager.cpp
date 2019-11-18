#include <enemy_manager.h>
#include <enemy.h>

Archetype GHOST("../../common/sprites/GhostEnemySingle.png", "../../common/sprites/FireballNoOutline.png",		true,     1, 6,    1, 1, 3, 4, Behavior::AIType::Simple,   glm::vec2(1.0f, 1.0f),     glm::vec2(0.4f));
Archetype REDGHOST("../../common/sprites/RedGhost.png", "../../common/sprites/RedFireball.png",					true,  1.2f, 6, 1.5f, 1, 4, 4, Behavior::AIType::Lead,     glm::vec2(1.0f, 1.0f),     glm::vec2(0.4f));
Archetype CRYINGGHOST("../../common/sprites/CryingGhost.png", "../../common/sprites/FireballNoOutline.png",		true,   .8f, 8,  .5f, 1, 1, 6, Behavior::AIType::Circle,   glm::vec2(1.0f, 1.0f),     glm::vec2(0.4f));
Archetype ABNORMALGHOST("../../common/sprites/AbnormalGhost.png", "../../common/sprites/AbnormalFireball.png",  true,   .5f, 5,    3, 1, 6, 2, Behavior::AIType::Circle,   glm::vec2(1.0f, 1.0f),     glm::vec2(1.4f));
Archetype SLIME("../../common/sprites/Slime.png", "../../common/sprites/FireballNoOutline.png",					false, 2.5f, 6,    1, 1, 3, 4, Behavior::AIType::Simple,   glm::vec2(0.4f, 0.4f),     glm::vec2(0.4f));
Archetype BIGSLIME("../../common/sprites/BigSlime.png", "../../common/sprites/FireballNoOutline.png",			false, 1.2f, 6,    2, 2, 3, 4, Behavior::AIType::Simple,   glm::vec2(1.2f, 1.2f),		glm::vec2(0.4f));
Archetype SPIDER("../../common/sprites/RedSpider.png", "../../common/sprites/WebShot.png",						true,     1, 7,    1, 1, 3, 5, Behavior::AIType::Cardinal, glm::vec2(0.5f, 0.5f),		glm::vec2(0.3f));

Archetype::Archetype(char* enemyTex, char* shotTex, bool doesShoot, float moveSpeed, float shotSpeed,
	float damage, int health, float shotFrequency, int radius, Behavior::AIType behave, glm::vec2 size, glm::vec2 shotSize)
{
	this->enemyTexture = enemyTex;
	this->shotTexture = shotTex;
	this->doesShoot = doesShoot;
	this->moveSpeed = moveSpeed;
	this->shotSpeed = shotSpeed;
	this->damage = damage;
	this->health = health;
	this->shotFrequency = shotFrequency;
	this->radius = radius;
	this->behavior = behave;
	this->size = size;
	this->shotSize = shotSize;
}

void GenerateEnemyRoom(DungeonTile* tiles)
{
	srand(time(NULL));
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float maxX = FLT_MIN; 
	float maxY = FLT_MIN;
	int tilesLen = sizeof tiles;
	for (int i = 0; i < tilesLen; i++) {
		if (tiles[i].getWorldX() > maxX) maxX = tiles[i].getWorldX();
		if (tiles[i].getWorldX() < minX) minX = tiles[i].getWorldX();
		if (tiles[i].getWorldY() > maxY) maxY = tiles[i].getWorldY();
		if (tiles[i].getWorldY() < minY) minY = tiles[i].getWorldY();
	}
	
	int numEnemies = (rand() % 10) + 1;
	std::vector<glm::vec2> enemies;
	int i = 0;
	glm::vec2 max = vec2(10, 10);
	glm::vec2 min = vec2(0, 0);
	//printf("mxX %f mxY %f\n", max.x, max.y);
	while (i < numEnemies) {
		glm::vec2 pos = GetRandomPos(max, min);
		bool farEnough = true;
		for (glm::vec2 p : enemies) {
			if (distance(pos, p) < .2) farEnough = false;
		}
		if (farEnough) {
			enemies.push_back(pos);
			i++;
		}
	}
	int scenario = 0;
	switch (numEnemies)
	{
	case 1:
		scenario = rand() % 3;
		switch (scenario)
		{
		case 0:
			GenerateEnemy(enemies.at(0), ABNORMALGHOST);
			break;
		case 1:
			GenerateEnemy(enemies.at(0), BIGSLIME);
			break;
		case 2:
			GenerateEnemy(enemies.at(0), REDGHOST);
			break;
		case 3:
			GenerateEnemy(enemies.at(0), CRYINGGHOST);
			break;
		default:
			break;
		}
		break;
	case 2:
		scenario = rand() % 5;
		switch (scenario)
		{
		case 0:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			break;
		case 1:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), BIGSLIME);
			break;
		case 2:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), REDGHOST);
			break;
		case 3:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), ABNORMALGHOST);
			break;
		case 4:
			GenerateEnemy(enemies.at(0), CRYINGGHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			break;
		default:
			break;
		}
		break;
	case 3:
		scenario = rand() % 9;
		switch (scenario)
		{
		case 0:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			break;
		case 1:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), BIGSLIME);
			GenerateEnemy(enemies.at(2), GHOST);
			break;
		case 2:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), REDGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			break;
		case 3:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), ABNORMALGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			break;
		case 4:
			GenerateEnemy(enemies.at(0), CRYINGGHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			break;
		case 5:
			GenerateEnemy(enemies.at(0), SPIDER);
			GenerateEnemy(enemies.at(1), SPIDER);
			GenerateEnemy(enemies.at(2), SPIDER);
			break;
		case 6:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), SLIME);
			GenerateEnemy(enemies.at(2), CRYINGGHOST);
			break;
		case 7:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), SLIME);
			GenerateEnemy(enemies.at(2), ABNORMALGHOST);
			break;
		case 8:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), BIGSLIME);
			break;
		default:
			break;
		}
		break;
	case 4:
		scenario = rand() % 10;
		switch (scenario)
		{
		case 0:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), CRYINGGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			break;
		case 1:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), BIGSLIME);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			break;
		case 2:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), REDGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			break;
		case 3:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), ABNORMALGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), SLIME);
			break;
		case 4:
			GenerateEnemy(enemies.at(0), CRYINGGHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), SLIME);
			break;
		case 5:
			GenerateEnemy(enemies.at(0), SPIDER);
			GenerateEnemy(enemies.at(1), SPIDER);
			GenerateEnemy(enemies.at(2), SPIDER);
			GenerateEnemy(enemies.at(3), BIGSLIME);
			break;
		case 6:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), SLIME);
			GenerateEnemy(enemies.at(2), CRYINGGHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			break;
		case 7:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), SLIME);
			GenerateEnemy(enemies.at(2), ABNORMALGHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			break;
		case 8:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), BIGSLIME);
			GenerateEnemy(enemies.at(3), REDGHOST);
			break;
		case 9:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), SLIME);
			GenerateEnemy(enemies.at(3), ABNORMALGHOST);
			break;
		default:
			break;
		}
		break;
	case 5:
		scenario = rand() % 10;
		switch (scenario)
		{
		case 0:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), CRYINGGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 1:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), BIGSLIME);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 2:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), REDGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 3:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), ABNORMALGHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), SLIME);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 4:
			GenerateEnemy(enemies.at(0), CRYINGGHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), GHOST);
			GenerateEnemy(enemies.at(3), SLIME);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 5:
			GenerateEnemy(enemies.at(0), SPIDER);
			GenerateEnemy(enemies.at(1), SPIDER);
			GenerateEnemy(enemies.at(2), SPIDER);
			GenerateEnemy(enemies.at(3), BIGSLIME);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 6:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), SLIME);
			GenerateEnemy(enemies.at(2), CRYINGGHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 7:
			GenerateEnemy(enemies.at(0), SLIME);
			GenerateEnemy(enemies.at(1), SLIME);
			GenerateEnemy(enemies.at(2), ABNORMALGHOST);
			GenerateEnemy(enemies.at(3), GHOST);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 8:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), BIGSLIME);
			GenerateEnemy(enemies.at(3), REDGHOST);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		case 9:
			GenerateEnemy(enemies.at(0), GHOST);
			GenerateEnemy(enemies.at(1), GHOST);
			GenerateEnemy(enemies.at(2), SLIME);
			GenerateEnemy(enemies.at(3), ABNORMALGHOST);
			GenerateEnemy(enemies.at(4), SPIDER);
			break;
		default:
			break;
		}
		break;
	case 6:
		scenario = rand() % 3;
		switch (scenario)
		{
		case 0:
			for (int i = 0; i < 6; i++) {
				GenerateEnemy(enemies.at(i), SLIME);
			}
			break;
		case 1:
			for (int i = 0; i < 6; i++) {
				GenerateEnemy(enemies.at(i), GHOST);
			}
			break;
		case 2:
			for (int i = 0; i < 4; i++) {
				GenerateEnemy(enemies.at(i), SPIDER);
			}
			GenerateEnemy(enemies.at(5), BIGSLIME);
			GenerateEnemy(enemies.at(6), ABNORMALGHOST);
			break;
		default:
			break;
		}
		break;
	case 7:
		scenario = rand() % 3;
		switch (scenario)
		{
		case 0:
			for (int i = 0; i < 7; i++) {
				GenerateEnemy(enemies.at(i), SLIME);
			}
			break;
		case 1:
			for (int i = 0; i < 7; i++) {
				GenerateEnemy(enemies.at(i), GHOST);
			}
			break;
		case 2:
			for (int i = 0; i < 5; i++) {
				GenerateEnemy(enemies.at(i), SPIDER);
			}
			GenerateEnemy(enemies.at(5), CRYINGGHOST);
			GenerateEnemy(enemies.at(6), CRYINGGHOST);
			break;
		default:
			break;
		}
		break;
	case 8:
		scenario = rand() % 3;
		switch (scenario)
		{
		case 0:
			for (int i = 0; i < 8; i++) {
				GenerateEnemy(enemies.at(i), SLIME);
			}
			break;
		case 1:
			for (int i = 0; i < 8; i++) {
				GenerateEnemy(enemies.at(i), GHOST);
			}
			break;
		case 2:
			for (int i = 0; i < 7; i++) {
				GenerateEnemy(enemies.at(i), SPIDER);
			}
			GenerateEnemy(enemies.at(7), REDGHOST);
			break;
		default:
			break;
		}
		break;
	case 9:
		scenario = rand() % 3;
		switch (scenario)
		{
		case 0:
			for (int i = 0; i < 9; i++) {
				GenerateEnemy(enemies.at(i), SPIDER);
			}
			break;
		case 1:
			for (int i = 0; i < 9; i++) {
				GenerateEnemy(enemies.at(i), GHOST);
			}
			break;
		case 2:
			for (int i = 0; i < 8; i++) {
				GenerateEnemy(enemies.at(i), SLIME);
			}
			GenerateEnemy(enemies.at(8), REDGHOST);
			break;
		default:
			break;
		}
		break;
	case 10:
		scenario = rand() % 1;
		switch (scenario)
		{
		case 0:
			for (int i = 0; i < 10; i++) {
				GenerateEnemy(enemies.at(i), SPIDER);
			}
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void GenerateEnemy(glm::vec2 pos, char* enemyTex, char* shotTex, bool doesShoot, float moveSpeed, float shotSpeed,
	float damage, int health, float shotFrequency, int radius, Behavior::AIType behave, glm::vec2 size, glm::vec2 shotSize)
{
	Archetype arch(enemyTex, shotTex, doesShoot, moveSpeed, shotSpeed, damage, health, shotFrequency, radius, behave, size, shotSize);
	GenerateEnemy(pos, arch);
}

void GenerateEnemy(glm::vec2 pos, Archetype arch)
{
	Enemy* e = new Enemy(pos, arch);
}

glm::vec2 GetRandomPos(glm::vec2 max, glm::vec2 min)
{
	int width =  (int)(max.x - min.x);
	int height = (int)(max.y - min.y);
	//printf("w%d h%d\n", width, height);
	glm::vec2 pos;
	pos.x = (rand() % width) + min.x;
	pos.y = (rand() % height) + min.y;
	return pos;
}