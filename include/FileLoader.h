#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string.h>

using namespace glm;

/* Public Functions */
GLuint LoadShader(const char * vertex_file_path,const char * fragment_file_path);

float* LoadBMP(const char* filepath);
#endif
