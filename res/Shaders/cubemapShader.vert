#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 2) in vec2 vTexCoord;

out vec3 textureDir;

layout (std140) uniform cameraMatrices
{
	mat4 projection;
	mat4 view;
};
uniform mat4 model;

void main()
{
	textureDir = vPos;
	vec4 pos = projection *view *model * vec4(vPos, 1.0);
	gl_Position = pos.xyww;
}