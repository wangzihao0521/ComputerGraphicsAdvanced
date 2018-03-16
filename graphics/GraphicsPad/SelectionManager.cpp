#include "SelectionManager.h"
#include <glm\gtc\matrix_transform.hpp>
#include "FrameBuffer.h"
#include "Object.h"

SelectionManager* SelectionManager::SltManager = nullptr;

void SelectionManager::init()
{
	SelectionPass = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\SelectionVertexShader.glsl", "Default\\ShaderFile\\SelectionFragmentShader.glsl");
	OutlinePass = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\OutlineVertexShader.glsl", "Default\\ShaderFile\\OutlineFragmentShader.glsl");
	SelectRadius = 5;
	SelectionMatrix = glm::mat4();
	FBO = new FrameBuffer();
	FBO->SelectionInit();
}

SelectionManager * SelectionManager::getInstance()
{
	if (SltManager)
		return SltManager;
	SltManager = new SelectionManager();
	return SltManager;
}

Pass * SelectionManager::getSelectionPass() const
{
	return SelectionPass;
}

Pass * SelectionManager::getOutlinePass() const
{
	return OutlinePass;
}

FrameBuffer * SelectionManager::getFBO() const
{
	return FBO;
}

void SelectionManager::UpdateSelectionMatrix(GLsizei width, GLsizei height, glm::vec2 ClipPos)
{
	glm::mat4 TranslateMatrix = glm::translate(glm::mat4(), glm::vec3(-ClipPos.x,-ClipPos.y,0));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(width / SelectRadius, height / SelectRadius, 1));
	SelectionMatrix = ScaleMatrix * TranslateMatrix;
}

void SelectionManager::SelectionRender(Object * obj, Object * cam_obj, GLsizei screenwidth, GLsizei screenheight,GLint id)
{
	if (!cam_obj)
		return;

	Camera* Camera_Component = cam_obj->getComponent<Camera>();
	if (!Camera_Component)
		return;
	if (obj->IsHided())
		return;

	Mesh* msh = nullptr;
	if (obj->getComponent<Mesh_Filter>())
		msh = obj->getComponent<Mesh_Filter>()->getMesh();

	else if (obj->getComponent<Light>())
	{
		if (obj->getComponent<Light>()->getLightType() == Light::Type::Point_Light)
			msh = Light::P_Light_Mesh;
		else if (obj->getComponent<Light>()->getLightType() == Light::Type::Directional)
			msh = Light::D_Light_Mesh;
	}
	if (!msh)
		return;
	
	glBindVertexArray(msh->getVArrayID());
	Transform* transform = obj->getComponent<Transform>();

	glm::mat4 CameraMatrix = Camera_Component->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = Camera_Component->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVPS = SelectionMatrix * Zihao_MVP;

	GLint uniformLocation;
	if (id > 0)					//id will be always greater than zero while doing selection, equals to zero while drawing outline.
	{
		uniformLocation = glGetUniformLocation(SelectionPass->getProgramID(), "Zihao_MVPS");
		if (uniformLocation >= 0)
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVPS[0][0]);

		uniformLocation = glGetUniformLocation(SelectionPass->getProgramID(), "ID");
		if (uniformLocation >= 0)
			glUniform1i(uniformLocation, id);
	}
	else
	{
		uniformLocation = glGetUniformLocation(OutlinePass->getProgramID(), "Zihao_MVP");
		if (uniformLocation >= 0)
			glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
	}
	unsigned int NumIndices = msh->getGeometry()->NF() * 3;
	glDrawArrays(GL_TRIANGLES, 0, NumIndices);
}

