#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include <entity.h>
#include <enemy.h>
#include <list>
#include <projectile.h>
#include <sword.h>
#include <player.h>
#include <list>

void EnterGameLoop(void);
void LeaveGameLoop(DungeonTile*);
void AddEntity(Entity* e);
void RemoveEntity(Entity* e);
Player* GetPlayer();
void SetPlayer(Player*);

std::list<Entity*> * GetEntityList(void);
#endif
