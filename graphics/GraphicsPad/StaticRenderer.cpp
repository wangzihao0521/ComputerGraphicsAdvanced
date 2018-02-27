#include "StaticRenderer.h"
#include "Object.h"

StaticRenderer* StaticRenderer::Static_Renderer = nullptr;

void StaticRenderer::init()
{
	pass = ShaderCompiler::getInstance()->Compile("StaticVertexShader.glsl", "StaticFragmentShader.glsl");
}

void StaticRenderer::Render(Mesh* mesh,Transform * transform, Object * cam, GLsizei screenwidth, GLsizei screenheight)
{
	glUseProgram(pass->getProgramID());
	glBindVertexArray(mesh->getVArrayID());
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBufferID());

	if (!cam)
		return;
	Camera* Camera_Component = cam->getComponent<Camera>();
	if (!Camera_Component)
		return;

	glm::mat4 CameraMatrix = Camera_Component->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = glm::mat4();
	if (Camera_Component->getPJ_Mode() == Perspective)
		projectionMatrix = glm::perspective(60.0f, ((float)screenwidth / screenheight), 0.3f, 500.0f);
	else if (Camera_Component->getPJ_Mode() == Orthogonal)
	{
		float distance = glm::distance(transform->getPosition(), cam->getComponent<Transform>()->getPosition());
		projectionMatrix = glm::ortho(-distance / 2, distance / 2, -distance / 2, distance / 2, 1.0f, 100.0f);
	}

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix =  glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
								glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
								glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1)) ;
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  TransformMatrix * RotationMatrix * ScaleMatrix;

	GLint MVPuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_MVP");
	if (MVPuniformLocation >= 0)
		glUniformMatrix4fv(MVPuniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);

	unsigned int NumIndices = mesh->getGeometry()->NF() * 3;
	glDrawArrays(GL_TRIANGLES, 0,NumIndices);
}


