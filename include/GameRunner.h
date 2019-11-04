#ifndef GAME_RUNNER_H
#define GAME_RUNNER_H

#include <entity.h>
#include <enemy.h>
#include <player.h>
#include <projectile.h>
#include <sword.h>

void EnterGameLoop(void);
void AddEntity(Entity* e);
void RemoveEntity(Entity* e);

#endif
