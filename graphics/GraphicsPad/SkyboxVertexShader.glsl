#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 normal;
in layout(location = 2) vec3 Vtx_uv;

out vec3 pos_UniformClipSpace;

void main()
{
	gl_Position = vec4 (position,1.0);
	pos_UniformClipSpace = position;
}
