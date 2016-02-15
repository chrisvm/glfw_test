#version 410 core

in vec3 Color;
in vec2 Texcoord;
out vec4 outColor;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
};

uniform DirectionalLight dirLight;
uniform sampler2D sampler;

void main(void) {
    outColor = texture(sampler, Texcoord) * vec4(Color, 1.0);
}