#version 430

in vec3 VertexPos_WS;
in vec4 VertexPos_LightClipPos;
out vec4 pixelcolor;

uniform vec3 LightPosition_WS;
uniform samplerCubeShadow ShadowMap;
uniform float farPlane;

void main()
{
	vec3 CubeMapUV = normalize(VertexPos_WS - LightPosition_WS);
	float Distance_L_F = length(VertexPos_WS - LightPosition_WS);
	Distance_L_F = Distance_L_F / farPlane;
	float bias = 0.98;
	Distance_L_F *= bias;
	float Shadow = texture (ShadowMap,vec4(CubeMapUV,Distance_L_F));
	if (Shadow > 0.8)
		discard;
	else if (Shadow > 0.2 )
		pixelcolor = vec4 (0,0,0,0.8-Shadow);
	else
		pixelcolor = vec4 (0,0,0,0.6);
}
