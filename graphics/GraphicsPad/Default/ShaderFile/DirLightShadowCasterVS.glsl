#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec3 normal;
in layout(location = 2) vec3 Vtx_uv;

out vec3 VertexPos_WS;
out vec2 uv;
out vec4 VertexPos_LightClipPos;

uniform mat4 Zihao_MVP;
uniform mat4 Zihao_M2W;
uniform mat4 LightMatrix_MVP;

void main()
{
	gl_Position = Zihao_MVP * vec4 (position,1.0);
	gl_Position.z -= 0.0001;
	VertexPos_WS = vec3(Zihao_M2W * vec4 (position,1.0));
	VertexPos_LightClipPos = LightMatrix_MVP * vec4 (position,1.0);
	uv = vec2 (Vtx_uv);
}
