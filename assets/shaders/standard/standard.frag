#version 410 core

in vec2 Texcoord;
in vec3 Normal;

out vec4 outColor;

struct DirectionalLight {
    vec3 color;
    float ambientIntensity;
};

uniform DirectionalLight dirLight;
uniform sampler2D sampler;

void main(void) {
    outColor = texture(sampler, Texcoord) * vec4(dirLight.color, 1.0f) * dirLight.ambientIntensity;
}