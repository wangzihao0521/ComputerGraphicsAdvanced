#version 430

in layout(location = 0) vec3 position;

out vec3 VertexPos_WS;
out vec4 VertexPos_LightClipPos0;
out vec4 VertexPos_LightClipPos1;
out vec4 VertexPos_LightClipPos2;
out vec4 VertexPos_LightClipPos3;

uniform mat4 Zihao_MVP;
uniform mat4 Zihao_M2W;
uniform mat4 LightMatrix_MVP0;
uniform mat4 LightMatrix_MVP1;
uniform mat4 LightMatrix_MVP2;
uniform mat4 LightMatrix_MVP3;

void main()
{
	gl_Position = Zihao_MVP * vec4 (position,1.0);
	gl_Position.z -= 0.0002;
	VertexPos_WS = vec3(Zihao_M2W * vec4 (position,1.0));
	VertexPos_LightClipPos0 = LightMatrix_MVP0 * vec4 (position,1.0);
	VertexPos_LightClipPos1 = LightMatrix_MVP1 * vec4 (position,1.0);
	VertexPos_LightClipPos2 = LightMatrix_MVP2 * vec4 (position,1.0);
	VertexPos_LightClipPos3 = LightMatrix_MVP3 * vec4 (position,1.0);
}
