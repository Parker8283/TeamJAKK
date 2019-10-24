
#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Texture.h"
#include "sprite_renderer.h"


class Entity
{
	
public:
	glm::vec2 Position;

	GLuint texture;
	GLuint VBO;
	GLuint VAO;
	GLuint UV;

	//float UV[12];

	int Height;
	int Width;
	GLfloat rotation;

	Entity();
	~Entity();

	void Init();
	void Render();
	void Update();
	glm::vec3 GetPos();
	GLuint GetVBO();
};


#endif
