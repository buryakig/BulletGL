#version 460 core
out vec4 FragColor;

in vec2 oTexCoord;

uniform sampler2D _MainTex;


void main()
{
	vec3 color  = texture(_MainTex, oTexCoord).rgb;

	float brightness = dot(color.rgb, vec3(0.2126, 0.7152, 0.0722));

	if(brightness > 1.0)
		FragColor = vec4(color, 1.0);
    else
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
}