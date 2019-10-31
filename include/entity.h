
#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Texture.h>
#include <glm/glm.hpp>
#include "helpers/RootDir.h.in"


class Entity
{
	
public:
	
	char* textureFilepath;
	GLuint VBO[2];
	GLuint VAO;
	// variables used in Drawing the entity
	GLuint texture;
	glm::vec2 Position;
	int Height;
	int Width;
	glm::vec2 size;
	GLfloat rotation;

	int uID;

	Entity(char* filepath);
	~Entity(void);

	void Init(glm::vec2);
	void Draw(void);
	virtual void Update(void) {};
	glm::vec3 GetPos(void);
	GLuint GetVBO(void);
	void SetUID(int);

	bool operator==(const Entity&);
};


#endif
