#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec3 camerapos;

uniform samplerCube cubemap;

void main()
{
	vec3 viewDir = normalize(Position - camerapos);
	vec3 reflectionDir = reflect(viewDir, normalize(Normal));
    FragColor = vec4(texture(cubemap, reflectionDir).rgb, 1.0);
}