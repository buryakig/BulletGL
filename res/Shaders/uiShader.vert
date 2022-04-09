#version 460 core
layout (location = 0) in vec2 Position;
layout (location = 1) in vec2 UV;
layout (location = 2) in vec4 Color;

layout(std140, binding = 0) uniform PerFrameData 
{
 uniform mat4 MVP;
};

out vec2 Frag_UV;
out vec4 Frag_Color;

void main()
{
    Frag_UV = UV;
    Frag_Color = Color;
    gl_Position = MVP * vec4(Position, 0.0, 1.0);
}