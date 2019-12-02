#include <Hud.h>
#include <GameRunner.h>
#include <glm/glm.hpp>
#include <TextBox.h>

FilledBox GreyBox = FilledBox(glm::vec4(-.95f, -.95f, -.45f, -.85f), glm::vec3(.3f));
FilledBox RedBox  = FilledBox(glm::vec4(1), glm::vec3(.75f, .1f, .05f));

void DrawHud(void) {
  /******************Draw Health******************/
  float scale = float(GetPlayer()->GetHealth()) / float(GetPlayer()->GetMaxHealth());
  RedBox.SetPos(glm::vec4(-.95f, -.95f, -.95f + .5f * scale, -.85f));

  GreyBox.Draw();
  RedBox.Draw();
  /***********************************************/

  /******************Draw Score*******************/



  
  /***********************************************/
}
