#include "entity.h"
#include <Graphics.h>
#include <GameRunner.h>

using namespace glm;

static int idCounter = 0;

static float UV[12]{
  0, 0,
  0, 1,
  1, 0,
  0, 1,
  1, 1,
  1, 0
};

static float verts[18]{
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

Entity::Entity(char* filepath)
{
	Entity::uID = idCounter + 1;
	idCounter++;
	Entity::textureFilepath = filepath;
}

Entity::~Entity(void)
{

}

void Entity::Init(glm::vec2 pos)
{
	Position.x = pos.x;
	Position.y = pos.y;
	texture = LoadTexture(textureFilepath);
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

	//AddEntity(this);
}

void Entity::Draw(void)
{
	mat4 M = glm::translate(mat4(1), Entity::GetPos());
	//printf("%f, %f\n", Entity::GetPos().x, Entity::GetPos().y);
	mat4 MVP = GetP() * GetView() * M;

	glBindVertexArray(Entity::VAO);
	glUseProgram(GetShader());
	
	glBindTexture(GL_TEXTURE_2D, Entity::texture);
	
	glUniform1i(glGetUniformLocation(GetShader(), "tex"), 0);

	glUniformMatrix2fv(glGetUniformLocation(GetShader(), "uvRot"), 1, GL_FALSE, &rot[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(GetShader(), "MVP"), 1, GL_FALSE, &MVP[0][0]);
	
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

glm::vec3 Entity::GetPos(void)
{
	return glm::vec3(Entity::Position, 0);
}

void Entity::Update(void)
{
	
}