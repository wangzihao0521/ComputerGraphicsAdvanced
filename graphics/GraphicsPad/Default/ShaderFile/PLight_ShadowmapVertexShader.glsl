#version 430

in layout(location = 0) vec3 position;

out vec3 VertexPos_WS;

uniform mat4 Zihao_MVP;
uniform mat4 Zihao_M2W;

void main()
{
	gl_Position = Zihao_MVP * vec4 (position,1.0);
	VertexPos_WS = vec3(Zihao_M2W * vec4 (position,1.0));
}
