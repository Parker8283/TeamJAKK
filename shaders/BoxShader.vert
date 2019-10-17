#version 330

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;

out vec2 frag_uv;

uniform sampler2D tex;
uniform mat2 uvRot;
uniform mat4 MVP;

void main() {
  frag_uv = uvRot * uv;
  gl_Position = MVP * vec4(vertex, 1.0f);
}
