#version 430

out vec4 pixelcolor;

uniform vec3 PureColor;
uniform float Alpha;

void main()
{
	pixelcolor = vec4(PureColor,Alpha);
//	pixelcolor = vec4(1,1,1,1);
}

