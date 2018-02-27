#version 430

in layout(location = 0) vec3 position;

uniform mat4 Zihao_MVP;

void main()
{
	vec4 Pos = Zihao_MVP * vec4 (position,1.0);
	Pos.z -= 0.001;
	gl_Position = Pos;
}
