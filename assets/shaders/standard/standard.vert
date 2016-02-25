#version 410 core

in vec3 position;
in vec2 texcoord;
in vec3 normal;

out vec2 Texcoord;
out vec3 Normal;
out vec3 WorldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main(void) {
    gl_Position = proj * view * model * vec4(position, 1.0);
    Texcoord = texcoord;
    Normal = (model * vec4(normal, 0.0)).xyz;
    WorldPos = (model * vec4(position, 1.0)).xyz;
}