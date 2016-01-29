#version 410 core

out vec4 outColor;
in vec3 Color;

void main(void) {
  outColor = vec4(Color, 1.0);
}