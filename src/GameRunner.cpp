#include <Controller.h>
#include <DungeonMap.h>
#include <GameRunner.h>
#include <glm/glm.hpp>
#include <Graphics.h>
#include <stdio.h>
#include <System.h>
#include <WindowManager.h>
#include <enemy_manager.h>
#include <vector>


static int cursor = 0;
static int enemiesKilled = 0;

static std::list< Entity* > entities;
static std::vector<Entity*> removeList;

static Player* player;

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
  enemiesKilled = 0;

  DungeonTile* map = GenerateTestRoom(10, 10);
  int numTiles = 10 * 10;

  SetPlayer(new Player);
  float timer = 0;

  GenerateEnemyRoom(map, numTiles);

  glClearColor(0, 0, 0, 1);
  RefreshSystemTimer();
  while (GetGameState() == GameState::RUN_GAME) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateSystemTimer();
    UpdateKeys();
    //UpdatePlayer();

    std::list<Entity*>::iterator it;

    //Update entities and gather garbage
    for (it = entities.begin(); it != entities.end(); ++it) {
      if (*it == NULL)
        break;
      
      if ((*it)->Update())
        removeList.push_back(*it);
    }

    //Remove and delete entities
    for (uint i = 0; i < removeList.size(); i++) {
      RemoveEntity(removeList[i]);
      delete removeList[i];
    }

    //Clear removeList
    removeList.clear();

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
    if (GetPlayer()->health <= 0) {
      LeaveGameLoop(map);
      break;
    }
  }
}

void LeaveGameLoop(DungeonTile* map) {
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SetControlContext(GameState::GAME_OVER);
  std::list<Entity*> ::iterator it;
  for (it = entities.begin(); it != entities.end(); ++it) {
    removeList.push_back(*it);
  }

  for (uint i = 0; i < removeList.size(); i++) {
    RemoveEntity(removeList[i]);
    delete removeList[i];
  }

  removeList.clear();
  entities.clear();
  
  UnpressKeys();
  SetGameState(GameState::GAME_OVER);
}

void IncrementEnemiesKilled() {
  enemiesKilled++;
}

int GetEnemiesKilled() {
  return enemiesKilled;
}
