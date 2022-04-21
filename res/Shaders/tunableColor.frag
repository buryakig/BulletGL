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

    if(projCoords.z > 1.0)
        return 0.0;

    float currentDepth = projCoords.z;
    float bias = 0.005;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int i = -1; i <= 1; ++i)
    {
        for(int j = -1; j <= 1; ++j)
        {
            float closestDepth = texture(shadowMap, projCoords.xy + vec2(i, j) * texelSize).r; 
            shadow += currentDepth - bias < closestDepth  ? 1.0 : 0.3;
        }
    }
    shadow /= 9.0;

    return shadow;
}

void main()
{
	//float shadow = CalculateShadows(FragPosLightSpace);
	FragColor = vec4(1.0, 0.0, 0.0, 1.0);//fColor;// * shadow;

}