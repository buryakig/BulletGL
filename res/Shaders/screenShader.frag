#version 460 core
out vec4 FragColor;

in vec2 oTexCoord;

uniform sampler2D _MainTex;
uniform sampler2D _BloomTex;


void main()
{
	vec3 hdrColorLinear  = texture(_MainTex, oTexCoord).rgb;
	vec3 bloomColor  = texture(_BloomTex, oTexCoord).rgb;

	hdrColorLinear += bloomColor;

	vec3 hdrColorMapped = vec3(1.0) - exp(-hdrColorLinear);
	// gamma correction 
	vec3 resultGamma = pow(hdrColorMapped.rgb, vec3(1.0/2.2));
	FragColor = vec4(resultGamma, 1.0);
	//FragColor = vec4(oTexCoord, 0.0, 1.0);
}