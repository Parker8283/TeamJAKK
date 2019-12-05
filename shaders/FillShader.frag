#version 330 core 

out vec4 fragColor;

uniform float brightness;
uniform vec4 color;

void main() {
  fragColor = vec4(brightness * color.xyz, color.a);
}
