#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec3 aNormal;
layout (location = 1) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Color;


layout(std140, binding = 0) uniform PerFrameData {
 uniform mat4 MVP;
 uniform vec3 cameraPos;
};

uniform mat4 model;

void main()
{
    gl_Position = MVP * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoord;
    Color = aColor;
}