#include <Controller.h>
#include <GameRunner.h>
#include <Graphics.h>
#include <stdio.h>
#include <System.h>
#include <WindowManager.h>
#include <helpers/RootDir.h.in>
#include <list>

std::list< Entity* > entities;
int cursor = 0;

void EnterGameLoop(void) {
  LoadPlayerControls();
  MakeGameRunControlContext();
  Enemy* e = new Enemy("../../common/sprites/GhostEnemySingle.png");
  e->Init(glm::vec2(1, 1));

  glClearColor(0, 0, 0, 1);
  RefreshSystemTimer();
  while (GetGameState() == GameState::RUN_GAME) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateSystemTimer();
    UpdatePlayer();

	std::list<Entity*> ::iterator it;
	for (it = entities.begin(); it != entities.end(); ++it)
	{
		(*it)->Update();
	}

    DrawPlayer();
	//e->Draw();
	for (it = entities.begin(); it != entities.end(); ++it)
	{
		//printf("Draw entities\n");
		(*it)->Draw();
	}
	
    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }
}

void AddEntity(Entity* e)
{
	printf("Adding entity\n");
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
