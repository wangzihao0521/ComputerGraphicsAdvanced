#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 normal;

out vec3 VertexNormal;
out vec3 VertexPos;

uniform mat4 Zihao_MVP; 

void main()
{
	gl_Position = Zihao_MVP * vec4 (position,1.0);
	VertexNormal = normal;
	VertexPos = position;
}

