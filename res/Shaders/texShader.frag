#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texImage;

void main()
{
   vec4 tex1col = texture(texImage, TexCoord);
   FragColor = tex1col;
}