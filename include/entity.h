
#ifndef ENTITY_H
#define ENTITY_H

#include <Collision.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Texture.h>
#include <glm/glm.hpp>

class Entity
{
	
public:
	CollisionBox hitBox;

	GLuint VBO[2];
	GLuint VAO;
	// variables used in Drawing the entity
	GLuint texture;
	glm::vec2 Position;
	float Height;
	float Width;
	glm::vec2 size;
	GLfloat rotation;
	float speed;
	

	int uID;

	Entity(glm::vec2 pos, const char* filepath);

	void Draw(void);
	void SetUID(int);

	bool operator==(const Entity&);
	
	virtual bool Update(void) { return false; };

	CollisionBox GetHitBox(void);
	
	GLuint GetVBO(void);
	
	glm::vec3 GetPos(void);
};


#endif
