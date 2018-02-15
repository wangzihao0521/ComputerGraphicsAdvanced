#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 normal;
in layout(location = 2) vec3 Vtx_uv;

out vec3 VertexNormal;
out vec3 VertexPos;
out vec2 uv;

uniform mat4 Zihao_MVP; 

void main()
{
	gl_Position = Zihao_MVP * vec4 (position,1.0);
	VertexNormal = normal;
	VertexPos = position;
	uv = vec2(Vtx_uv);
}

