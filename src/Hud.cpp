#include <Hud.h>
#include <GameRunner.h>
#include <glm/glm.hpp>
#include <string.h>
#include <stdio.h>
#include <TextBox.h>


static FilledBox greyBox = FilledBox(glm::vec4(-.95f, -.95f, -.45f, -.85f), glm::vec4(.3f, .3f, .3f, 1.0f));
static FilledBox redBox  = FilledBox(glm::vec4(1), glm::vec4(.75f, .1f, .05f, 1.0f));

static TextBox scoreBox  = TextBox("", glm::vec4(-.95f, -.8f, -.85f, -.7f));
 
char score[64] = {0};

void DrawHud(void) {
  /******************Draw Health******************/
  float scale = float(GetPlayer()->GetHealth()) / float(GetPlayer()->GetMaxHealth());
  redBox.SetPos(glm::vec4(-.95f, -.95f, -.95f + .5f * scale, -.85f));

  greyBox.Draw();
  redBox.Draw();
  /***********************************************/

  /******************Draw Score*******************/
  memset(score, 0, sizeof(score));
  snprintf(score, sizeof(score), "Score: %u", GetPlayer()->score);
  scoreBox.SetAlignment(LEFT);
  scoreBox.SetText(score);
  scoreBox.Draw();
  /***********************************************/
}
