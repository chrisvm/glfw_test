#version 410 core

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec2 Texcoord;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void) {
    Texcoord = texcoord;
    Normal = normal;
    gl_Position = proj * view * model * vec4(position, 1.0);
}