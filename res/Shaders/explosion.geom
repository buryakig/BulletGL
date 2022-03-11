#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Color;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

vec4 explode(vec4 position, vec3 normal)
{
	float magnitude = 2.0;
	vec3 direction = normal * magnitude;
	return position + vec4(direction, 0.0);
}

void main()
{
	vec3 normal = GetNormal();

	gl_Position = explode(gl_in[0].gl_Position, normal);
	EmitVertex();
	
	gl_Position = explode(gl_in[1].gl_Position, normal);
	EmitVertex();
	
	gl_Position = explode(gl_in[2].gl_Position, normal);
	EmitVertex();

	EndPrimitive();
}