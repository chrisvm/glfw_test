#version 410 core

in vec3 position;
in vec3 color;

out vec3 Color;
void main(void) {
    Color = color;
    gl_Position = vec4(position, 1.0);
}