
#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Texture.h>
#include <glm/glm.hpp>


class Entity
{
	
public:

	glm::vec2 Position;

	GLuint texture;
	char* textureFilepath;
	GLuint VBO[2];
	GLuint VAO;

	//float UV[12];

	int Height;
	int Width;
	GLfloat rotation;

	int uID;

	Entity(char* filepath);
	~Entity(void);

	void Init(glm::vec2);
	void Draw(void);
	void Update(void);
	glm::vec3 GetPos(void);
	GLuint GetVBO(void);
};


#endif
