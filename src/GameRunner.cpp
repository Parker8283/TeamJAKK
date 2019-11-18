#include <Controller.h>
#include <DungeonMap.h>
#include <GameRunner.h>
#include <glm/glm.hpp>
#include <Graphics.h>
#include <stdio.h>
#include <System.h>
#include <WindowManager.h>
#include <list>
#include <enemy_manager.h>

static std::list< Entity* > entities;
static int cursor = 0;
Player* player;

using namespace glm;

void AddEntity(Entity* e)
{
  //printf("Adding entity\n");
  entities.push_back(e);
  e->SetUID(cursor);
  cursor++;
}

std::list<Entity*> * GetEntityList(void) {
  return &entities;
}

void RemoveEntity(Entity* e)
{
  std::list<Entity*> ::iterator it;
  for (it = entities.begin(); it != entities.end(); ++it)
  {
    if ((*it)->uID == e->uID)
    {
      entities.erase(it);
      break;
    }
  }
}

Player* GetPlayer() {
	return player;
}

void SetPlayer(Player* play) {
	player = play;
}

void EnterGameLoop(void) {
  LoadPlayerControls();
  SetControlContext(GameState::RUN_GAME);

  DungeonTile* map = GenerateTestRoom();

  GenerateEnemyRoom(map);

  player = new Player();

  glClearColor(0, 0, 0, 1);
  RefreshSystemTimer();
  while (GetGameState() == GameState::RUN_GAME) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateSystemTimer();
	UpdateKeys();
    //UpdatePlayer();

    std::list<Entity*>::iterator it;

    for (it = entities.begin(); it != entities.end(); ++it) {
      if (*it == NULL)
        break;
      (*it)->Update();
    }

    for (uint i = 0; i < 100; i++) {
      map[i].Draw();
    }

    //DrawPlayer();
    for (it = entities.begin(); it != entities.end(); ++it)
    {
      //printf("Draw entities\n");
      (*it)->Draw();
    }

    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }
}




