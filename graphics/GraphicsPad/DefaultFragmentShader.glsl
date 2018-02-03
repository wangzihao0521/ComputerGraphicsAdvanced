#version 430

in vec3 VertexNormal;
in vec3 VertexPos;
out vec4 pixelcolor;

uniform mat4 Zihao_M2W;
uniform vec3 Zihao_ViewPosition_WS;
uniform vec3 Zihao_LightPosition_WS;
uniform vec3 Zihao_AmbientColor;

void main()
{
	vec3 VertexNormal_WS = vec3 (transpose(inverse(Zihao_M2W)) * vec4(VertexNormal,0));
	vec3 VertexPos_WS = vec3(Zihao_M2W * vec4(VertexPos,1.0));

	vec3 lightVector = normalize(Zihao_LightPosition_WS - VertexPos_WS);
	float brightness = clamp(dot(lightVector, VertexNormal_WS),0,1);
	vec3 DiffuseLight = vec3(brightness,brightness,brightness);

	vec3 viewdirection = normalize(Zihao_ViewPosition_WS - VertexPos_WS);
	vec3 Half = normalize(lightVector + viewdirection);
	float SpecularIntensity = pow(clamp(dot(Half,VertexNormal_WS),0,1),50);
	vec3 SpecularLight = SpecularIntensity * vec3(1.0,0.0,0.0);

	vec3 AmbientLight = Zihao_AmbientColor;

	pixelcolor = vec4(DiffuseLight + SpecularLight + AmbientLight,1.0);
}