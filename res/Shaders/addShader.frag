#version 460 core
out vec4 FragColor;

in vec2 oTexCoord;

uniform bool horizontal;

uniform sampler2D _MainTex;

uniform float weight[5] = float[](0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{
	vec2 texSize = textureSize(_MainTex, 0);
	float texOffset = (1.0 / texSize.y);

	vec3 color  = texture(_MainTex, oTexCoord).rgb * weight[0];

	for(int i = 1; i < 5; ++i)
	{
		vec2 duv = vec2(0.0, texOffset * i);
		color += texture(_MainTex, oTexCoord + duv).rgb * weight[i];
		color += texture(_MainTex, oTexCoord - duv).rgb * weight[i];
	}
	
	FragColor = vec4(color, 1.0);
}