#version 460 core
layout (location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform PerFrameData {
 uniform mat4 MVP;
 uniform vec3 cameraPos;
};

layout(std140, binding = 1) uniform LightData { 
 uniform mat4 lightSpaceMatrix;
};

out vec4 FragPosLightSpace;
uniform mat4 model;

void main()
{
    FragPosLightSpace = lightSpaceMatrix * vec4(vec3(model * vec4(aPos, 1.0)), 1.0);
    gl_Position = MVP * model * vec4(aPos, 1.0);
}