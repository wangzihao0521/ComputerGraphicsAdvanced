#version 430

in vec3 VertexPos_WS;
in vec4 VertexPos_LightClipPos;
in vec2 uv;
out vec4 pixelcolor;

uniform vec3 LightPosition_WS;
uniform sampler2DShadow ShadowMap;
uniform float farPlane;

void main()
{
	vec2 Shadowmap_uv = vec2(VertexPos_LightClipPos.x /VertexPos_LightClipPos.w , VertexPos_LightClipPos.y/ VertexPos_LightClipPos.w) *0.5 +0.5;
	float Distance_F_L = length(VertexPos_WS - LightPosition_WS);
	Distance_F_L = Distance_F_L / farPlane;
	float bias = 0.97;
	Distance_F_L *= bias;
	float Shadow = texture (ShadowMap,vec3(Shadowmap_uv,Distance_F_L));

//	pixelcolor = vec4(Shadow,Shadow,Shadow,1);
//	if (Shadow>0 && Shadow < 1)
//	pixelcolor = vec4(0.5,0.5,0.5,1);

	if (Shadow > 0.8)
		discard;
	else if (Shadow > 0.2 )
		pixelcolor = vec4 (0,0,0,0.8-Shadow);
	else
		pixelcolor = vec4 (0,0,0,0.6);
}
