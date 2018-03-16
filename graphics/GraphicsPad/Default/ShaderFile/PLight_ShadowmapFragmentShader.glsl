#version 430

in vec3 VertexPos_WS;
out float gl_FragDepth;

uniform vec3 LightPosition_WS;
uniform float farPlane;

void main()
{
	float Distance_L_F = length(VertexPos_WS - LightPosition_WS);
	gl_FragDepth = Distance_L_F / farPlane;
}
