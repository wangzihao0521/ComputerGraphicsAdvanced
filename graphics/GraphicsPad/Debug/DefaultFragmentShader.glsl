#version 430

in vec3 VertexPos;
out vec4 pixelcolor;

void main()
{
	pixelcolor = vec4(VertexPos,1.0);
}