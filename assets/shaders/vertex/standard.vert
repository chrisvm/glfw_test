#version 410 core

in vec3 position;
in vec3 vColor;

void main(void)
{
  gl_Position = vec4(position, 1.0);
}