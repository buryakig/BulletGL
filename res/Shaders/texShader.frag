#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D texImage;

void main()
{
   vec4 tex1col = texture(texImage, texCoord);
   FragColor = tex1col;
}