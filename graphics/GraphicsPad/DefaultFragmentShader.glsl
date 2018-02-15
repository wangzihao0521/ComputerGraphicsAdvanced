#version 430

in vec3 VertexNormal;
in vec3 VertexPos;
in vec2 uv;
out vec4 pixelcolor;

uniform mat4 Zihao_M2W;
uniform vec3 Zihao_ViewPosition_WS;
uniform vec4 Zihao_LightPosition_WS;
uniform vec3 Zihao_AmbientColor;
uniform sampler2D DeFt_Mtl_map_Ka;
uniform sampler2D DeFt_Mtl_map_Kd;
uniform sampler2D DeFt_Mtl_map_Ks;
uniform vec3 DeFt_Mtl_Ka;
uniform vec3 DeFt_Mtl_Kd;
uniform vec3 DeFt_Mtl_Ks;
uniform vec3 DeFt_Mtl_Tf;
uniform float DeFt_Mtl_Ns;

void main()
{
	vec3 VertexNormal_WS = vec3 (normalize(transpose(inverse(Zihao_M2W)) * vec4(VertexNormal,0)));
	vec3 VertexPos_WS = vec3(Zihao_M2W * vec4(VertexPos,1.0));

	vec3 lightVector = mix(-Zihao_LightPosition_WS.rgb,normalize(Zihao_LightPosition_WS.rgb - VertexPos_WS),Zihao_LightPosition_WS.a);
	float brightness = clamp(dot(lightVector, VertexNormal_WS),0,1);
	vec3 DiffuseLight = vec3(brightness,brightness,brightness);
	vec3 DiffuseColor = vec3(texture(DeFt_Mtl_map_Kd,uv)) * DiffuseLight * DeFt_Mtl_Kd;

	vec3 viewdirection = normalize(Zihao_ViewPosition_WS - VertexPos_WS);
	vec3 Half = normalize(lightVector + viewdirection);
	float SpecularIntensity = pow(clamp(dot(Half,VertexNormal_WS),0,1),DeFt_Mtl_Ns);
	vec3 SpecularLight = SpecularIntensity * vec3(1.0,1.0,1.0);
	vec3 SpecularColor = vec3(texture(DeFt_Mtl_map_Ks,uv)) * SpecularLight * DeFt_Mtl_Ks;

	vec3 AmbientLight = Zihao_AmbientColor;
	vec3 AmbientColor = vec3(texture(DeFt_Mtl_map_Ka,uv)) * AmbientLight * DeFt_Mtl_Ka;

	pixelcolor = vec4(DiffuseColor + SpecularColor + AmbientColor,1.0);
//	pixelcolor = vec4(SpecularColor+AmbientColor,1.0);
//	pixelcolor = vec4(VertexNormal_WS,1.0);
//	pixelcolor = texture(DeFt_Mtl_map_Kd,uv);
}