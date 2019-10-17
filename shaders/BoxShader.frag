#version 330

in vec2 frag_uv;

out vec4 color;

uniform sampler2D tex;

void main() {
  color = texture(tex, frag_uv);
  //color = vec4(1, 1, 1, 1);
}
