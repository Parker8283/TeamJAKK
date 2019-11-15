#version 330 core  //OpenGL version 3.3

in  vec2 TexCoords;
out vec4 color;

uniform sampler2D tex;

uniform float textBrightness;
uniform vec3  textColor;

void main()
{
  color = vec4(textBrightness * textColor, texture(tex, TexCoords).r);
  //color = vec4(1);
}
