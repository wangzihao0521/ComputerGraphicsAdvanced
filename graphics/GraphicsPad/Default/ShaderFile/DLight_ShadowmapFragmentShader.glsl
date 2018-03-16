#version 430

in vec3 VertexPos_WS;
in vec4 gl_FragCoord;
out float gl_FragDepth;

uniform vec3 LightPosition_WS;
uniform float farPlane;

void main()
{
	float Distance_L_F = length(VertexPos_WS - LightPosition_WS);
//	gl_FragDepth = gl_FragCoord.z;
	gl_FragDepth = Distance_L_F / farPlane;
//	if (gl_FragCoord.z<0.999)
//		gl_FragDepth = 0.5;
}
