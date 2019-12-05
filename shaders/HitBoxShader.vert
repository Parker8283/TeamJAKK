#version 330 core

layout (location = 0) in vec2 vertex;

uniform mat4 MVP;

void main() {
  gl_Position = MVP * vec4(vertex, 0.0f, 1.0f);
}
