#version 410 core

out vec4 color;
uniform vec3 triangleColor;

void main(void)
{
  color = vec4(triangleColor, 1.0);
}