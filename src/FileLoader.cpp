#define GLM_ENABLE_EXPERIMENTAL
#include <algorithm>
#include <FileLoader.h>
#include <float.h>
#include <fstream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;
using namespace glm;

/* Reads characters until a newline character is reached
 * **Doesn't keep the newline character */
/*
static void readLine(char* dest, FILE* file) {
	char ch;
	char buf[4096] = {0};

	int i;
	int ret;
	for (i = 0; i < 4096; i++) {
		ret = fread(&ch, 1, 1, file);
		if (ret == 0)
			break;

		if (ch == '\n')
			break;
		buf[i] = ch;
	}

	strncpy(dest, buf, 4096);
}

static void readToken(char* dest, FILE* file) {
	char ch;
	char buf[256] = {0};

	while (1) {
		fread(&ch, 1, 1, file);

		if (ch != ' ') {
			break;
		}
	}

	int i = 0;
	if (ch != '<') {
		buf[0] = ch;
		i = 1;
	} else {
		i = 0;
	}

	for (; i < 256; i++) {
		fread(&ch, 1, 1, file);
		if (ch == ' ' || ch == '>' || ch == '<')
			break;
		buf[i] = ch;
	}

	strncpy(dest, buf, 256);
}

 * Read file until a library is reached.  The file
 * cursor will be at the beginning of the next line immediately
 * after the library */ /*
static void readLibrary(char* dest, FILE* file) {
	char buf[256] = {0};
	char line[4096] = {0};
	while (1) {
		memset(buf, 0, sizeof(buf));
		readToken(buf, file);
		readLine(line, file);

		if (strcmp(buf, "library_geometries") == 0)
			break;
		if (strcmp(buf, "library_animations") == 0)
			break;
		if (strcmp(buf, "library_controllers") == 0)
			break;
		if (strcmp(buf, "library_visual_scenes") == 0)
			break;
		if (strcmp(buf, "/COLLADA") == 0)
			break;
	}
	strncpy(dest, buf, sizeof(buf));
}

static void getParamValue(char* id, char* value, FILE* file) {
	char ch;
	char buf[256]   = {0};

	memset(id, 0, 32);
	memset(value, 0, 224);

	readToken(buf, file);

	if (buf[0] == '\0')
		return;

	int cur = 0;
	for (int i = 0; i < 32; i++) {
		ch = buf[cur++];
		if (ch == '=')
			break;

		id[i] = ch;
	}

	int idCur = 0;
	int count = 0;
	for (int i = 0; i < 224; i++) {
		ch = buf[cur++];

		if (ch == '"') {
			count++;
			continue;
		}

		if (count == 2)
			break;

		value[idCur++] = ch;
	}
}

static void getParam(char* id, char* value, const char* param, FILE* file) {
	char buf[32]  = {0};
	char val[224] = {0};

	while (strcmp(buf, param) != 0) {
		memset(buf, 0, sizeof(buf));
		memset(val, 0, sizeof(val));
		getParamValue(buf, val, file);
	}

	memset(id, 0, 32);
	memset(value, 0, 224);

	strncpy(id, buf, 32);
	strncpy(value, val, 224);
}

static mat4 getTransform(FILE* file) {
	char buf[256]   = {0};

	mat4 transform;
	for (int k = 0; k < 4; k++) {
		for (int l = 0; l < 4; l++) {
			memset(buf, 0, sizeof(buf));
			readToken(buf, file);

			transform[l][k] = strtof(buf, NULL);
		}
	}

	return transform;
}
*/

float* LoadBMP(const char* filepath) {
	uint fileSize;
	uint arrayOffset;

	float* heights;
	FILE* file = fopen(filepath, "rb");

	if (file == NULL) {
		perror(filepath);
		return NULL;
	}

	// Read in pixel array offset
	fseek(file, 0x0A, SEEK_SET);
	fread(&arrayOffset, sizeof(uint), 1, file);

	// Read in pixel array size in bytes
	fseek(file, 0x22, SEEK_SET);
	fread(&fileSize, sizeof(uint), 1, file);

	heights = (float*) malloc(fileSize);

	fseek(file, arrayOffset, SEEK_SET);


	size_t readIn = fread(heights, sizeof(uint), fileSize / sizeof(uint), file);
	if ((readIn*sizeof(uint)) != fileSize) {
		printf("Failed to read entire file %s\n", filepath);
		fclose(file);
		free(heights);
		return NULL;
	}

	fclose(file);
	return heights;
}

GLuint LoadShader(const char * vertex_file_path, const char * fragment_file_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << VertexShaderStream.rdbuf();
		VertexShaderCode = sstr.str();
		VertexShaderStream.close();
	} else {
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::stringstream sstr;
		sstr << FragmentShaderStream.rdbuf();
		FragmentShaderCode = sstr.str();
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	//printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	//printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	//printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
