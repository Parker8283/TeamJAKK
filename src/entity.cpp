#include "entity.h"
#include <Graphics.h>
#include <GameRunner.h>

using namespace glm;

static int idCounter = 0;

static float UV[12] {
  0, 0,
  0, 1,
  1, 0,
  0, 1,
  1, 1,
  1, 0
};

static float verts[18] {
  -1, -1, 0,
  -1,  1, 0,
  1,  -1, 0,
  -1,  1, 0,
  1,  1, 0,
  1, -1, 0
};

static const glm::mat2 rot = {
  -1,  0,
  0, -1
};

Entity::Entity(vec2 pos, const char* filepath)
{
	speed = 1;

  uID = idCounter + 1;
  idCounter++;

  rotation = 0;
  Width = 1;
  Height = 1;
  size = glm::vec2(Width, Height);
  Position = glm::vec2(0, 0);

  Position.x = pos.x;
  Position.y = pos.y;

  hitBox = CollisionBox(1, 1, Position);

  texture = LoadTexture(filepath);
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(2, VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

  glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(UV), UV, GL_STATIC_DRAW);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  AddEntity(this);
}

void Entity::Draw(void)
{
  glUseProgram(GetShader());

  mat4 M = glm::translate(mat4(1), GetPos());
  //printf("%f, %f\n", GetPos().x, GetPos().y);
  
  mat4 MVP = GetProjection() * GetView() * M;

  MVP = glm::translate(MVP, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); //Move origin to center to rotate
  MVP = glm::rotate(MVP, rotation, glm::vec3(0.0f, 0.0f, 1.0f)); //Then rotate
  MVP = glm::translate(MVP, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move the origin back

  MVP = glm::scale(MVP, glm::vec3(size, 1.0f)); // Last scale

  glBindVertexArray(VAO);

  glBindTexture(GL_TEXTURE_2D, texture);

  glUniform1i(glGetUniformLocation(GetShader(), "tex"), 0);

  glUniformMatrix2fv(glGetUniformLocation(GetShader(), "uvRot"), 1, GL_FALSE, &rot[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(GetShader(), "MVP"), 1, GL_FALSE, &MVP[0][0]);

  glDrawArrays(GL_TRIANGLES, 0, 6);
}

bool Entity::Update() {
	hitBox.SetPos(Position);
	return false;
}

bool Entity::CheckWalls(glm::vec2 pos) {
	CollisionBox hit = CollisionBox(Width, Height, pos + glm::vec2(.2, .2));
	int num = 0;
	std::vector<DungeonTile> walls = GetCurrentRoomWalls();
	std::vector<DungeonTile>::iterator it;

	for (it = walls.begin(); it != walls.end(); ++it) {
		if (checkCollision(it->GetHitBox(), hit)) {
			return true;
		}
	}

	return false;
}

glm::vec2 Entity::CheckEntities(glm::vec2 pos, std::list<Entity*>* e) {
	CollisionBox hit = CollisionBox(Width, Height, pos);
	
	std::list<Entity*>::iterator it;

	for (it = e->begin(); it != e->end(); ++it) {
		if ((*it) != this) {
			glm::vec2 res = CheckEntity(pos, (*it));
			if (res != pos) {
				return res;
			}
		}
	}

	return pos;
}

glm::vec2 Entity::CheckEntity(glm::vec2 pos, Entity* e) {
	CollisionBox hit = CollisionBox(Width, Height, pos);

	if (checkCollision(hit, e->GetHitBox())) {
		glm::vec2 nextX = glm::vec2(pos.x, Position.y);
		glm::vec2 nextY = glm::vec2(Position.x, pos.y);
		if (CheckWalls(nextX) /**&& !CheckWalls(nextY)*/) {
			return nextY;
		}
		else if (CheckWalls(nextY) /**&& !CheckWalls(nextX)*/) {
			return nextX;
		}
		else {
			return Position;
		}
	}

	return pos;
}

CollisionBox Entity::GetHitBox(void) {
  return this->hitBox;
}

glm::vec3 Entity::GetPos(void)
{
  return vec3(Entity::Position, 0);
}

void Entity::SetUID(int id)
{
  uID = id;
}

bool Entity::operator==(const Entity& e)
{
  return this->uID == e.uID;
}
