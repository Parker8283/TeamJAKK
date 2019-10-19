#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <WindowManager.h>

static int xRes, yRes;

static GLFWwindow* window;

static void loadWindowSettings(void) {
  xRes = 1920;
  yRes = 1080;
}

int CreateWindow(void) {
  loadWindowSettings();

  // Initialise GLFW
  if ( !glfwInit() ) {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
  }

  //Setup window parameters
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
  glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
  glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
  glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_FALSE);

  window = glfwCreateWindow(xRes, yRes, "Sword Thrower", NULL, NULL);

  //Setup Window
  if (window == NULL) {
    fprintf( stderr, "GLFW failed to create window\n");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  //Initialize glew
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    return 1;
  }

  glfwSetWindowPos(window, 0, 0);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  glfwSetCursorPos(window, xRes / 2, yRes / 2);

  glDisable(GL_CULL_FACE);

  /* Turn off/on V-Sync off(0) on(1) */
  glfwSwapInterval(0);

  /* Cull Back Faces when culling is enabled */
  glCullFace(GL_BACK);

  /* Enable OpenGL blending (a.k.a transparency) */
  glEnable(GL_BLEND);
  glEnable(GL_LINE_SMOOTH);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  /* Enable depth test (culls triangles that are behind other drawn triangles using depth testing) */
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);

  return 0;
}

GLFWwindow* GetWindow(void) {
  return window;
}
