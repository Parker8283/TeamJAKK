#ifndef CONTROL_H
#define CONTROL_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <map>

#define MOUSE_OFFSET 1000

typedef struct KeyFunction {
  void (*function1)(void*);
  void (*function2)(void*);
  void* data;
} KeyFunction;

typedef std::map<int, KeyFunction> FuncMap;

void ActivateKey(int key);
void ActivateMouse(int key);

/* Binds int_key (given by GLFW_ENUM) to an activated and deactivated function  
 * @param: _key - the GLFW_ENUM of the key wished to be binded
 * @param: activate   - a function pointer to a function that is called on the press of a key/mouse button  
 * @param: deactivate - a function pointer to a function that is called on the release of a key/mouse button
 * *note: function pointers are passed simply as the naked name of the function.  
 * *note: activate and/or deactivate can be NULL
 */
void BindKey(int _key, void (*activate)(void *), void (*deactivate)(void *), void* data);

/* Binds int_key (given by GLFW_ENUM) to an activated and deactivated function  
 * @param: _key - the GLFW_ENUM of the mouse button wished to be binded
 * @param: activate   - a function pointer to a function that is called on the press of a key/mouse button  
 * @param: deactivate - a function pointer to a function that is called on the release of a key/mouse button
 * *note: function pointers are passed simply as the naked name of the function.  
 * *note: activate and/or deactivate can be NULL
 */
void BindMouse(int _key, void (*activate)(void *), void (*deactivate)(void *), void *data);
void DeActivateKey(int _key);
void DeActivateMouse(int _key);
void UnBindKey(int _key);
void UnBindAll(void);
#endif
