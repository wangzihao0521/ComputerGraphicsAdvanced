#version 430

in layout(location = 0) vec3 position;

out vec3 VertexPos;

uniform mat4 Zihao_MVP;

void main()
{
	gl_Position = Zihao_MVP * vec4 (position,1.0);
	VertexPos = position;
}
