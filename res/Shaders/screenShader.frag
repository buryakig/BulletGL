#version 330 core
out vec4 FragColor;

in vec2 oTexCoord;

uniform sampler2D screenTex;

const float offset = 0.00333;

void main()
{

	vec2 offsets[9] = {
        vec2(-offset,  offset), // top-left
        vec2( 0.0f,    offset), // top-center
        vec2( offset,  offset), // top-right
        vec2(-offset,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset,  0.0f),   // center-right
        vec2(-offset, -offset), // bottom-left
        vec2( 0.0f,   -offset), // bottom-center
        vec2( offset, -offset)  // bottom-right    
    };

	// kernel vlues respective to the offsets
    float kernel[9] = {
        1.0,  1.0, 1.0,
        1.0, -8.0, 1.0,
        1.0,  1.0, 1.0 
    };
	
	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
	{
		col += texture(screenTex, oTexCoord.st + offsets[i]).rgb * kernel[i];
	}

	FragColor = vec4(texture(screenTex, oTexCoord).rgb, 1.0);
}