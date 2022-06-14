#version 330 core
out vec4 FragColor;

in vec2 oTexCoord;

uniform sampler2D screenTex;


void main()
{
	vec3 hdrColorLinear  = texture(screenTex, oTexCoord).rgb;
	
	vec3 hdrColorMapped = vec3(1.0) - exp(-hdrColorLinear);
	// gamma correction 
	vec3 resultGamma = pow(hdrColorMapped.rgb, vec3(1.0/2.2));
	FragColor = vec4(resultGamma, 1.0);
	//FragColor = vec4(oTexCoord, 0.0, 1.0);
}