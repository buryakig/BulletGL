#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

vec3 quad[6] = vec3[](
    vec3( 1.0, -1.0, 0.0),
    vec3(-1.0, -1.0, 0.0),
    vec3(-1.0,  1.0, 0.0),

    vec3( 1.0, -1.0, 0.0),
    vec3(-1.0, 1.0, 0.0),
    vec3( 1.0,  1.0, 0.0)
); 

vec2 quadUV[6] =vec2[](
    vec2( 1.0, 0.0),
    vec2( 0.0, 0.0),
    vec2( 0.0,  1.0),
       
    vec2( 1.0, 0.0),
    vec2( 0.0, 1.0),
    vec2( 1.0,  1.0)
); 

out vec2 oTexCoord;

void main()
{
    oTexCoord = vec2(quadUV[gl_VertexID].x, quadUV[gl_VertexID].y);
    gl_Position =  vec4(quad[gl_VertexID].x, quad[gl_VertexID].y, 0.0, 1.0);
}