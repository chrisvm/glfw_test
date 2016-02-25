#version 410 core

in vec2 Texcoord;
in vec3 Normal;
in vec3 WorldPos;

out vec4 outColor;

struct DirectionalLight {
    vec3 color;
    vec3 direction;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
    float specularPower;
};

uniform DirectionalLight dirLight;
uniform sampler2D sampler;
uniform vec3 EyeWorldPos;

void main(void) {
    vec4 ambientColor = vec4(dirLight.color, 1.0f) * dirLight.ambientIntensity;

    vec4 diffuseColor = vec4(0, 0, 0, 0);
    vec4 specularColor = vec4(0, 0, 0, 0);

    float diffuseFactor = dot(normalize(Normal), -dirLight.direction);
    if (diffuseFactor > 0) {
        diffuseColor = vec4(dirLight.color * dirLight.diffuseIntensity * diffuseFactor, 1.0f);

        vec3 vertexToEye = normalize(EyeWorldPos - WorldPos);
        vec3 lightReflect = normalize(reflect(dirLight.direction, normalize(Normal)));
        float specularFactor = dot(vertexToEye, lightReflect);
        if (specularFactor > 0) {
            specularFactor = pow(specularFactor, dirLight.specularPower);
            specularColor = vec4(dirLight.color * specularFactor * dirLight.specularIntensity, 1.0f);
        }
    }

    outColor = texture(sampler, Texcoord) * (ambientColor + diffuseColor + specularColor);
}