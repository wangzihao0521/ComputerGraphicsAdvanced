#version 430

in vec3 clipPos;
out int pixelcolor;
//out vec4 pixelcolor;

uniform int ID;

void main()
{
	pixelcolor = ID;
}

