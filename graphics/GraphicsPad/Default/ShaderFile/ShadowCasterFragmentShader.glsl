#version 430

in vec3 VertexPos_WS;
in vec4 VertexPos_LightClipPos0;
in vec4 VertexPos_LightClipPos1;
in vec4 VertexPos_LightClipPos2;
in vec4 VertexPos_LightClipPos3;
out vec4 pixelcolor;

uniform vec4 LightPosition_WS0;
uniform vec4 LightPosition_WS1;
uniform vec4 LightPosition_WS2;
uniform vec4 LightPosition_WS3;
uniform samplerCubeShadow ShadowMap3D0;
uniform samplerCubeShadow ShadowMap3D1;
uniform samplerCubeShadow ShadowMap3D2;
uniform samplerCubeShadow ShadowMap3D3;
uniform sampler2DShadow ShadowMap2D0;
uniform sampler2DShadow ShadowMap2D1;
uniform sampler2DShadow ShadowMap2D2;
uniform sampler2DShadow ShadowMap2D3;
uniform float farPlane0;
uniform float farPlane1;
uniform float farPlane2;
uniform float farPlane3;
uniform float LightIntensity0;
uniform float LightIntensity1;
uniform float LightIntensity2;
uniform float LightIntensity3;
uniform float LightRadius0;
uniform float LightRadius1;
uniform float LightRadius2;
uniform float LightRadius3;
uniform int LightCount;

void main()
{
	float bias = 0.98;
	float ShadowP0 = 0;
	float ShadowP1 = 0;
	float ShadowP2 = 0;
	float ShadowP3 = 0;
	float ShadowD0 = 0;
	float ShadowD1 = 0;
	float ShadowD2 = 0;
	float ShadowD3 = 0;
	float Shadow = 0;
	float Light_Intensity0 = 0;
	float Light_Intensity1 = 0;
	float Light_Intensity2 = 0;
	float Light_Intensity3 = 0;
	if (LightPosition_WS0.w == 1)
	{
		vec3 CubeMapUV0 = normalize(VertexPos_WS - vec3(LightPosition_WS0));
		float Distance_L_F0 = length(VertexPos_WS - vec3(LightPosition_WS0));
		Light_Intensity0 = LightIntensity0 * (1.0/(1+(1/(LightRadius0 * LightRadius0 * 0.5)) * Distance_L_F0 * Distance_L_F0));
		Distance_L_F0 = Distance_L_F0 / farPlane0 * bias;

		ShadowP0 = texture (ShadowMap3D0,vec4(CubeMapUV0,Distance_L_F0));
	}
	else 
	{
		bias = 0.995;
		vec2 Shadowmap_uv0 = vec2(VertexPos_LightClipPos0.x /VertexPos_LightClipPos0.w , VertexPos_LightClipPos0.y/ VertexPos_LightClipPos0.w) *0.5 +0.5;
		float Distance_F_L0 = length(VertexPos_WS - vec3(LightPosition_WS0));
		Distance_F_L0 = Distance_F_L0 / farPlane0 * bias;
		ShadowD0 = texture (ShadowMap2D0,vec3(Shadowmap_uv0,Distance_F_L0));
		Light_Intensity0 = LightIntensity0;
	}
	if (LightCount > 1)
	{
		if (LightPosition_WS1.w == 1)
		{
			vec3 CubeMapUV1 = normalize(VertexPos_WS - vec3(LightPosition_WS1));
			float Distance_L_F1 = length(VertexPos_WS - vec3(LightPosition_WS1));
			Light_Intensity1 = LightIntensity1 * (1.0/(1+(1/(LightRadius1 * LightRadius1 * 0.5)) * Distance_L_F1 * Distance_L_F1));
			Distance_L_F1 = Distance_L_F1 / farPlane1 * bias;

			ShadowP1 = texture (ShadowMap3D1,vec4(CubeMapUV1,Distance_L_F1));
		}
		else 
		{
			bias = 0.995;
			vec2 Shadowmap_uv1 = vec2(VertexPos_LightClipPos1.x /VertexPos_LightClipPos1.w , VertexPos_LightClipPos1.y/ VertexPos_LightClipPos1.w) *0.5 +0.5;
			float Distance_F_L1 = length(VertexPos_WS - vec3(LightPosition_WS1));
			Distance_F_L1 = Distance_F_L1 / farPlane1 * bias;
			ShadowD1 = texture (ShadowMap2D1,vec3(Shadowmap_uv1,Distance_F_L1));
			Light_Intensity1 = LightIntensity1;
		}
	}
	if (LightCount > 2)
	{
		if (LightPosition_WS2.w == 1)
		{
			vec3 CubeMapUV2 = normalize(VertexPos_WS - vec3(LightPosition_WS2));
			float Distance_L_F2 = length(VertexPos_WS - vec3(LightPosition_WS2));
			Light_Intensity2 = LightIntensity2 * (1.0/(1+(1/(LightRadius2 * LightRadius2 * 0.5)) * Distance_L_F2 * Distance_L_F2));
			Distance_L_F2 = Distance_L_F2 / farPlane2 * bias;

			ShadowP2 = texture (ShadowMap3D2,vec4(CubeMapUV2,Distance_L_F2));
		}
		else 
		{
			bias = 0.995;
			vec2 Shadowmap_uv2 = vec2(VertexPos_LightClipPos2.x /VertexPos_LightClipPos2.w , VertexPos_LightClipPos2.y/ VertexPos_LightClipPos2.w) *0.5 +0.5;
			float Distance_F_L2 = length(VertexPos_WS - vec3(LightPosition_WS2));
			Distance_F_L2 = Distance_F_L2 / farPlane2 * bias;
			ShadowD2 = texture (ShadowMap2D2,vec3(Shadowmap_uv2,Distance_F_L2));
			Light_Intensity2 = LightIntensity2;
		}
	}
	if (LightCount > 3)
	{
		if (LightPosition_WS3.w == 1)
		{
			vec3 CubeMapUV3 = normalize(VertexPos_WS - vec3(LightPosition_WS3));
			float Distance_L_F3 = length(VertexPos_WS - vec3(LightPosition_WS3));
			Light_Intensity3 = LightIntensity3 * (1.0/(1+(1/(LightRadius3 * LightRadius3 * 0.5)) * Distance_L_F3 * Distance_L_F3));
			Distance_L_F3 = Distance_L_F3 / farPlane3 * bias;

			ShadowP3 = texture (ShadowMap3D3,vec4(CubeMapUV3,Distance_L_F3));
		}
		else 
		{
			bias = 0.995;
			vec2 Shadowmap_uv3 = vec2(VertexPos_LightClipPos3.x /VertexPos_LightClipPos3.w , VertexPos_LightClipPos3.y/ VertexPos_LightClipPos3.w) *0.5 +0.5;
			float Distance_F_L3 = length(VertexPos_WS - vec3(LightPosition_WS3));
			Distance_F_L3 = Distance_F_L3 / farPlane3 * bias;
			ShadowD3 = texture (ShadowMap2D3,vec3(Shadowmap_uv3,Distance_F_L3));
			Light_Intensity3 = LightIntensity3;
		}
	}
//	Shadow = (ShadowP0 + ShadowD0 + ShadowP1 + ShadowD1 +ShadowP2 + ShadowD2 +ShadowP3 + ShadowD3 )/LightCount;
	Shadow = ((ShadowP0 + ShadowD0) * Light_Intensity0 + (ShadowP1 + ShadowD1) * Light_Intensity1 + (ShadowP2 + ShadowD2) * Light_Intensity2 + (ShadowP3 + ShadowD3) * Light_Intensity3 ) / (Light_Intensity0 + Light_Intensity1 + Light_Intensity2 + Light_Intensity3);
	if (Shadow > 0.7)
		discard;
	else
		pixelcolor = vec4 (0,0,0,pow((0.7-Shadow),1.5));
//	pixelcolor = vec4(Shadow,Shadow,Shadow,1);
}
