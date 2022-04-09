#version 460 core
in vec2 Frag_UV;
in vec4 Frag_Color;

layout (binding = 0) uniform sampler2D Texture;
layout (location = 0) out vec4 FragColor;

void main()
{
	FragColor = Frag_Color * texture(Texture, Frag_UV.st);
}