#version 330 core

in vec4 gl_FragCoord;
in vec4 FragPosLightSpace;

uniform sampler2D shadowMap;
uniform vec4 fColor;

out vec4 FragColor;


float CalculateShadows(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
    float bias = 0.005;
    float shadow = currentDepth - bias < closestDepth  ? 1.0 : 0.3;

    return shadow;
}

void main()
{
	float shadow = CalculateShadows(FragPosLightSpace);
	FragColor = fColor * shadow;

}