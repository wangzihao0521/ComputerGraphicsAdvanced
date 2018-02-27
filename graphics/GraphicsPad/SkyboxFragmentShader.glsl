#version 430

in vec3 pos_UniformClipSpace;
out vec4 pixelcolor;

uniform mat4 inverse_P;
uniform samplerCube CubeMap;

void main()
{
	vec3 uv = vec3(inverse_P * vec4(pos_UniformClipSpace,1.0));
	pixelcolor = texture(CubeMap,-uv);
}
