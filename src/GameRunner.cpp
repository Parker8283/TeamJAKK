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

using namespace glm;

void AddEntity(Entity* e)
{
  //printf("Adding entity\n");
  entities.push_back(e);
  e->SetUID(cursor);
  cursor++;
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

void EnterGameLoop(void) {
  LoadPlayerControls();
  SetControlContext(GameState::RUN_GAME);

  DungeonTile* map = GenerateTestRoom();

  GenerateEnemyRoom(map);

  Sword s("../../common/sprites/Sword1.png");
  s.Init();

  glClearColor(0, 0, 0, 1);
  RefreshSystemTimer();
  while (GetGameState() == GameState::RUN_GAME) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateSystemTimer();
    UpdatePlayer();

  for (uint i = 0; i < 100; i++) {
    map[i].Draw();
  }
  
	std::list<Entity*>::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->Update();
	}

    DrawPlayer();
	for (it = entities.begin(); it != entities.end(); ++it)
	{
		//printf("Draw entities\n");
		(*it)->Draw();
	}
	
    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }
}




