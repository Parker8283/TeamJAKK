
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

	Texture2D texture;
	SpriteRenderer* Renderer;

	GLuint Height;
	GLuint Width;

	Entity();
	~Entity();

	void Init();
	void render();
	
};


#endif
