#version 330 core
out vec4 FragColor;

in vec3 textureDir;

uniform samplerCube cubemap;

void main()
{
   vec4 tex1col = texture(cubemap, textureDir);
   FragColor = vec4(tex1col.rgb, 1.0);
}