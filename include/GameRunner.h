#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include <entity.h>
#include <enemy.h>
#include <list>
#include <player.h>
#include <projectile.h>
#include <sword.h>

void EnterGameLoop(void);
void AddEntity(Entity* e);
void RemoveEntity(Entity* e);

std::list<Entity*> * GetEntityList(void);
#endif
