#version 430

in layout(location = 0) vec3 position;

uniform mat4 Zihao_MVPS;

out vec3 clipPos;

void main()
{
	gl_Position = Zihao_MVPS * vec4 (position,1.0);
	clipPos = vec3(Zihao_MVPS * vec4 (position,1.0));
}

