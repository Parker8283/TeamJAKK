#include <Controller.h>
#include <GameRunner.h>
#include <Graphics.h>
#include <stdio.h>
#include <System.h>
#include <WindowManager.h>
#include <helpers/RootDir.h.in>

void EnterGameLoop(void) {
  LoadPlayerControls();
  MakeGameRunControlContext();
  Entity* e = new Entity(ROOT_DIR"/common/sprites/GhostEnemySingle.png");
  e->Init(glm::vec2(1, 1));

  glClearColor(0, 0, 0, 1);
  RefreshSystemTimer();
  while (GetGameState() == GameState::RUN_GAME) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    UpdateSystemTimer();
    UpdatePlayer();
	//for (auto i = entities.begin(); i != entities.end(); ++i)
	//{
		e->Update();
	//}

    DrawPlayer();
	//for (auto i = entities.begin(); i != entities.end(); ++i)
	//{
		e->Draw();
	//}

    glfwPollEvents();
    glfwSwapBuffers(GetWindow());
  }
}

/**void AddEntity(Entity* e)
{
	entities.push_back(*e);
}

void RemoveEntity(Entity e)
{
	for (auto i = entities.begin(); i != entities.end(); ++i)
	{
		if (i->uID == e.uID) {
			entities.erase(i);
		}
	}
}*/
