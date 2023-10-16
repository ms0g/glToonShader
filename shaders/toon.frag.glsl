#version 410 core

uniform vec3 viewPos;

in vec3 vNormal;
in vec3 vPosition;

out vec4 fragColor;

float inverseLerp(float minValue, float maxValue, float v) {
    return (v - minValue) / (maxValue - minValue);
}

float remap(float inMin, float inMax, float outMin, float outMax, float v) {
    float t = inverseLerp(inMin, inMax, v);
    return mix(outMin, outMax, t);
}


void main() {
    vec3 modelColour = vec3(0.5);
    vec3 lighting = vec3(0.0);

    vec3 normal = normalize(vNormal);
    vec3 viewDir = normalize(viewPos - vPosition);

    // Ambient
    vec3 ambient = vec3(1.0);

    // Hemi
    vec3 skyColour = vec3(0.0, 0.3, 0.6);
    vec3 groundColour = vec3(0.6, 0.3, 0.1);

    vec3 hemi = mix(groundColour, skyColour, remap(-1.0, 1.0, 0.0, 1.0, normal.y));

    // Diffuse lighting
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    vec3 lightColour = vec3(1.0, 1.0, 0.9);
    float dp = max(0.0, dot(lightDir, normal));

    float fullShadow = smoothstep(0.5, 0.505, dp);

    // Calculate the partially shadowed area by doing another step, but using a
    // higher threshold value than the fully shadowed area. Make the output from
    // this step 0.5 in the partially shadowed area, and 1.0 in the lit area.
    float partialShadow = mix(0.5, 1.0, smoothstep(0.65, 0.655, dp));

    // In this last step, you combine them.
    dp = min(partialShadow, fullShadow);

    vec3 specular = vec3(0.0);
    vec3 diffuse = dp * lightColour;

    // Specular
    vec3 r = normalize(reflect(-lightDir, normal));
    float phongValue = max(0.0, dot(viewDir, r));
    phongValue = pow(phongValue, 128.0);

    // Fresnel
    float fresnel = 1.0 - max(0.0, dot(viewDir, normal));
    fresnel = pow(fresnel, 2.0);
    fresnel *= step(0.7, fresnel);

    specular += phongValue;
    specular = smoothstep(0.5, 0.51, specular);

    lighting = hemi * (fresnel + 0.2) + diffuse * 0.8;

    vec3 colour = modelColour * lighting + specular;

    fragColor = vec4(pow(colour, vec3(1.0 / 2.2)), 1.0);

}