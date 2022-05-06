#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aColor;
layout (location = 4) in vec3 aTangent;
layout (location = 5) in vec3 aBiTangent;

out vec3 Normal;
out vec3 Tangent;
out vec3 BiTangent;
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
    
    mat3 vectorMatrix = transpose(inverse(mat3(model)));
    Normal = vectorMatrix * aNormal;
    Tangent = vectorMatrix * aTangent;
    BiTangent = vectorMatrix * aBiTangent;

    TexCoord = aTexCoord;
    Color = aColor;
}