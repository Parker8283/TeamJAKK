#include <Control.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>

#define MOUSE_OFFSET 1000

static FuncMap funcMap;

void ActivateKey(int key) {
  void (*function)(void*) = funcMap[key].function1;
  void* data              = funcMap[key].data;
  if (function != NULL)
    (*function)(data);
}

void ActivateMouse(int key) {
  ActivateKey(key + MOUSE_OFFSET);
}

/* Binds int_key (given by GLFW_ENUM) to an activated and deactivated function  
 * @param: _key - the GLFW_ENUM of the key wished to be binded
 * @param: activate   - a function pointer to a function that is called on the press of a key/mouse button  
 * @param: deactivate - a function pointer to a function that is called on the release of a key/mouse button
 * *note: function pointers are passed simply as the naked name of the function.  
 * *note: activate and/or deactivate can be NULL
 */
void BindKey(int _key, void (*activate)(void *), void (*deactivate)(void *), void* data) {
  KeyFunction func = { activate, deactivate, data };
  std::pair<FuncMap::iterator, bool> result = funcMap.insert(std::pair<int, KeyFunction>(_key, func));
  if (!result.second) {
    funcMap.erase(_key);
    funcMap.insert(std::pair<int, KeyFunction>(_key, func));
  }
}

/* Binds int_key (given by GLFW_ENUM) to an activated and deactivated function  
 * @param: _key - the GLFW_ENUM of the mouse button wished to be binded
 * @param: activate   - a function pointer to a function that is called on the press of a key/mouse button  
 * @param: deactivate - a function pointer to a function that is called on the release of a key/mouse button
 * *note: function pointers are passed simply as the naked name of the function.  
 * *note: activate and/or deactivate can be NULL
 */
void BindMouse(int _key, void (*activate)(void *), void (*deactivate)(void *), void *data) {
  BindKey(_key + MOUSE_OFFSET, activate, deactivate, data);
}

void DeActivateKey(int _key) {
  void (*function)(void*) = funcMap[_key].function2;
  void* data              = funcMap[_key].data;
  if (function != NULL)
    (*function)(data);
}

void DeActivateMouse(int _key) {
  DeActivateKey(_key + MOUSE_OFFSET);
}

void UnBindKey(int _key) {
  funcMap.erase(_key);
}

void UnBindAll(void) {
  funcMap.clear();
}
