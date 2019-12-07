#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include <entity.h>
#include <enemy.h>
#include <list>
#include <projectile.h>
#include <sword.h>
#include <player.h>
#include <list>
#include <irrklang/IrrKlang.h>

void EnterGameLoop(void);
void LeaveGameLoop(DungeonTile*);
void AddEntity(Entity* e);
void RemoveEntity(Entity* e);
void AddEnemy(Entity*);
void RemoveEnemy(Entity*);
Player* GetPlayer();
void SetPlayer(Player*);
int GetEnemiesKilled();
void IncrementEnemiesKilled();
std::vector<DungeonTile> GetCurrentRoomWalls();
irrklang::ISoundEngine* GetSoundEngine();

std::list<Entity*> * GetEntityList(void);
std::list<Entity*> * GetEnemyList(void);
#endif
