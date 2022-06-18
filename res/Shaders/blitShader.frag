#version 460 core
out vec4 FragColor;

in vec2 oTexCoord;

uniform sampler2D _MainTex;


void main()
{
	vec3 color  = texture(_MainTex, oTexCoord).rgb;
	
	FragColor = vec4(color * vec3(0.5, 0.0, 0.0), 1.0);
}