#include <Controller.h>
#include <DungeonMap.h>
#include <Hud.h>
#include <GameRunner.h>
#include <glm/glm.hpp>
#include <Graphics.h>
#include <MainMenu.h>
#include <stdio.h>
#include <System.h>
#include <WindowManager.h>
#include <enemy_manager.h>
#include <vector>

static int cursor = 0;
static int enemiesKilled = 0;

static std::list< Entity* > entities;
static std::list<Entity*> enemies;
static std::vector<Entity*> removeList;
static DungeonMap masterMap;
irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
float tim = 0;

static Player* player;

using namespace glm;

void AddEntity(Entity* e)
{
  entities.push_back(e);
  e->SetUID(cursor);
  cursor++;
}

void AddEnemy(Entity* e) {
	enemies.push_back(e);
}

void RemoveEnemy(Entity* e) {
	enemies.remove(e);
}

std::list<Entity*>* GetEnemyList(void) {
	return &enemies;
}

std::list<Entity*> * GetEntityList(void) {
  return &entities;
}

irrklang::ISoundEngine* GetSoundEngine() {
	return SoundEngine;
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

  int testX = 20;
  int testY = 20;
  //DungeonTile* map = GenerateTestRoom(testX, testY);
  DungeonTile* map = Doomsday();
  int numTiles = testX * testY;
  masterMap = DungeonMap(&map, testX, testY);

  SetPlayer(new Player);

  GenerateEnemyRoom(masterMap.getPassableList());

  glClearColor(0, 0, 0, 1);
  RefreshSystemTimer();
  SoundEngine->play2D("common/sounds/song.wav", GL_TRUE);
  while (GetGameState() == GameState::RUN_GAME || GetGameState() == GameState::PAUSE_GAME) {
    if (GetGameState() == GameState::PAUSE_GAME) {
      PauseGame();
      RefreshSystemTimer();
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateSystemTimer();
    UpdateKeys();

    //Draw Map
    for (uint i = 0; i < numTiles; i++) {
      map[i].Draw();
    }

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

    //Draw All entities
    for (it = entities.begin(); it != entities.end(); ++it)
    {
      (*it)->Draw();
    }

    //Draw Hud
    DrawHud();

	if (GetEnemyList()->size() == 0) {
		tim += GetFrameDeltaTime();
		if (tim > 4) {
			GenerateEnemyRoom(masterMap.getPassableList());
			GetPlayer()->curHealth += 3;
			if (GetPlayer()->GetHealth() > GetPlayer()->maxHealth) {
				GetPlayer()->curHealth = GetPlayer()->maxHealth;
			}
			tim = 0;
		}

	}

    if (GetPlayer()->GetHealth() <= 0) {
		SoundEngine->stopAllSounds();
	  GetSoundEngine()->play2D("common/sounds/death.wav", GL_FALSE);
      LeaveGameLoop(map);
      break;
    }
    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
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

std::vector<DungeonTile> GetCurrentRoomWalls() {
	return masterMap.getImpassableList();
}
