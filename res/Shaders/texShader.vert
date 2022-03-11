#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 2) in vec2 vTexCoord;
layout (location = 3) in vec3 vColor;

out vec3 vertexColor;
out vec2 texCoord;


layout (std140) uniform cameraMatrices
{
	mat4 projection;
	mat4 view;
};
uniform mat4 model;

void main()
{
   vertexColor = vColor;
   texCoord = vTexCoord;
   gl_Position = projection *view *model * vec4(vPos, 1.0);
}