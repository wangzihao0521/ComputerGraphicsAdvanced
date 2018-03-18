#include "SkyBox.h"
#include "glm\glm.hpp"
#include "GL\glew.h"
#include "Material.h"
#include "Object.h"

SkyBox* SkyBox::skybox = nullptr;

void SkyBox::init()
{
	vertices[0].position = cyPoint3f(-1.0, -1.0, 1.0);
	vertices[0].normal = cyPoint3f(0.0, 0.0, 1.0);
	vertices[0].uv = cyPoint3f(0.0, 0.0, 0.0);
	vertices[1].position = cyPoint3f(1.0, -1.0, 1.0);
	vertices[1].normal = cyPoint3f(0.0, 0.0, 1.0);
	vertices[1].uv = cyPoint3f(1.0, 0.0, 0.0);
	vertices[2].position = cyPoint3f(-1.0, 1.0, 1.0);
	vertices[2].normal = cyPoint3f(0.0, 0.0, 1.0);
	vertices[2].uv = cyPoint3f(0.0, 1.0, 0.0);
	vertices[3].position = cyPoint3f(1.0, -1.0, 1.0);
	vertices[3].normal = cyPoint3f(0.0, 0.0, 1.0);
	vertices[3].uv = cyPoint3f(1.0, 0.0, 0.0);
	vertices[4].position = cyPoint3f(1.0, 1.0, 1.0);
	vertices[4].normal = cyPoint3f(0.0, 0.0, 1.0);
	vertices[4].uv = cyPoint3f(1.0, 1.0, 0.0);
	vertices[5].position = cyPoint3f(-1.0, 1.0, 1.0);
	vertices[5].normal = cyPoint3f(0.0, 0.0, 1.0);
	vertices[5].uv = cyPoint3f(0.0, 1.0, 0.0);

	cubemap = TextureManager::getInstance()->ImportTex3D("Default\\Texture\\sL.png",
		"Default\\Texture\\sR.png",
		"Default\\Texture\\sD.png",
		"Default\\Texture\\sU.png",
		"Default\\Texture\\sF.png",
		"Default\\Texture\\sB.png"
	);

	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex_data), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &GeometryID);
	glBindVertexArray(GeometryID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

	pass = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\SkyboxVertexShader.glsl", "Default\\ShaderFile\\SkyboxFragmentShader.glsl");

	glActiveTexture(GL_TEXTURE31);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap->getTextureID());
}

void SkyBox::Render(Object * cam, GLsizei screenwidth, GLsizei screenheight)
{
	glUseProgram(pass->getProgramID());
	glBindVertexArray(GeometryID);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBufferID());

	if (!cam)
		return;
	Camera* Camera_Component = cam->getComponent<Camera>();
	if (!Camera_Component)
		return;

	glm::mat4 CameraMatrix = Camera_Component->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = Camera_Component->getProjectionMatrix();

	CameraMatrix[3][0] = 0;
	CameraMatrix[3][1] = 0;
	CameraMatrix[3][2] = 0;
	glm::mat4 inverse_P = glm::inverse(projectionMatrix * CameraMatrix);

	GLint uniformLocation = glGetUniformLocation(pass->getProgramID(), "inverse_P");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &inverse_P[0][0]);
	uniformLocation = glGetUniformLocation(pass->getProgramID(), "CubeMap");
	if (uniformLocation >= 0)
		glUniform1i(uniformLocation, 31);

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

SkyBox * SkyBox::getInstance()
{
	if (skybox)
	{
		return skybox;
	}
	skybox = new SkyBox();
	return skybox;
}



