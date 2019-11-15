#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <Control.h>

void SaveWindowSettings(void);

/*
 *  Returns non-zero value on failure.
 */
int CreateWindow(void);

glm::vec2 GetWindowResolution(void);
GLFWwindow* GetWindow(void);

#endif
