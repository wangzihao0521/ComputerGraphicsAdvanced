#include "StaticRenderer.h"
#include "Renderer.h"


StaticRenderer* StaticRenderer::Static_Renderer = nullptr;

void StaticRenderer::init()
{
	pass = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\StaticVertexShader.glsl", "Default\\ShaderFile\\StaticFragmentShader.glsl");
	pass_shadowmap_PLight = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\PLight_ShadowmapVertexShader.glsl", "Default\\ShaderFile\\PLight_ShadowmapFragmentShader.glsl");
	pass_shadowmap_DLight = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\DLight_ShadowmapVertexShader.glsl", "Default\\ShaderFile\\DLight_ShadowmapFragmentShader.glsl");
	pass_shadowcaster = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\PointLightShadowCasterVS.glsl", "Default\\ShaderFile\\PointLightShadowCasterFS.glsl");
	pass_shadowcaster_Dir = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\DirLightShadowCasterVS.glsl", "Default\\ShaderFile\\DirLightShadowCasterFS.glsl");
	pass_shadowcaster_ALL = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\ShadowCasterVertexShader.glsl", "Default\\ShaderFile\\ShadowCasterFragmentShader.glsl");
}

void StaticRenderer::Render(Mesh* mesh,Transform * transform, Object * cam)
{
	glUseProgram(pass->getProgramID());
	glBindVertexArray(mesh->getVArrayID());

	if (!cam)
		return;
	Camera* Camera_Component = cam->getComponent<Camera>();
	if (!Camera_Component)
		return;

	glm::mat4 CameraMatrix = Camera_Component->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = Camera_Component->getProjectionMatrix();

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

void StaticRenderer::Render_Shadowmap_PLight(Mesh * mesh, Transform * transform, Camera * cam_obj)
{
	glUseProgram(pass_shadowmap_PLight->getProgramID());
	glBindVertexArray(mesh->getVArrayID());

	glm::mat4 CameraMatrix = cam_obj->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = cam_obj->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  Zihao_M2W;

	GLint uniformLocation = glGetUniformLocation(pass_shadowmap_PLight->getProgramID(), "Zihao_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowmap_PLight->getProgramID(), "Zihao_M2W");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowmap_PLight->getProgramID(), "LightPosition_WS");
	if (uniformLocation >= 0)
		glUniform3fv(uniformLocation, 1, &cam_obj->getObject()->getComponent<Transform>()->getPosition()[0]);
	uniformLocation = glGetUniformLocation(pass_shadowmap_PLight->getProgramID(), "farPlane");
	if (uniformLocation >= 0)
		glUniform1f(uniformLocation,cam_obj->getFarPlane());

	unsigned int NumIndices = mesh->getGeometry()->NF() * 3;
	glDrawArrays(GL_TRIANGLES, 0, NumIndices);
}

void StaticRenderer::Render_Shadowmap_DLight(Mesh * mesh, Transform * transform, Camera * cam_obj)
{
	glUseProgram(pass_shadowmap_DLight->getProgramID());
	glBindVertexArray(mesh->getVArrayID());
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBufferID());

	glm::mat4 CameraMatrix = cam_obj->getDLight_Shadow_ViewMatrix();

	glm::mat4 projectionMatrix = cam_obj->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  Zihao_M2W;

	GLint uniformLocation = glGetUniformLocation(pass_shadowmap_DLight->getProgramID(), "Zihao_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);

	uniformLocation = glGetUniformLocation(pass_shadowmap_DLight->getProgramID(), "Zihao_M2W");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	//uniformLocation = glGetUniformLocation(pass_shadowmap_DLight->getProgramID(), "Zihao_M2W");
	//if (uniformLocation >= 0)
	//	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowmap_DLight->getProgramID(), "LightPosition_WS");
	if (uniformLocation >= 0)
		glUniform3fv(uniformLocation, 1, &cam_obj->getVirtualCamPos()[0]);
	uniformLocation = glGetUniformLocation(pass_shadowmap_DLight->getProgramID(), "farPlane");
	if (uniformLocation >= 0)
		glUniform1f(uniformLocation, cam_obj->getFarPlane());

	unsigned int NumIndices = mesh->getGeometry()->NF() * 3;
	glDrawArrays(GL_TRIANGLES, 0, NumIndices);
}

void StaticRenderer::RenderShadow(Mesh* mesh, Transform* transform, Camera * cam, Light * light)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(pass_shadowcaster->getProgramID());
	glBindVertexArray(mesh->getVArrayID());
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBufferID());
	glm::mat4 CameraMatrix = cam->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = cam->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  Zihao_M2W;
	Camera* Lightcam = light->getShadowInfo()->cam_Shadow;
	glm::mat4 LightMatrix_MVP = Lightcam->getProjectionMatrix() * Lightcam->getWorldToViewMatrix() *Zihao_M2W;
	GLint uniformLocation = glGetUniformLocation(pass_shadowcaster->getProgramID(), "Zihao_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster->getProgramID(), "Zihao_M2W");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster->getProgramID(), "LightMatrix_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &LightMatrix_MVP[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster->getProgramID(), "LightPosition_WS");
	if (uniformLocation >= 0)
		glUniform3fv(uniformLocation, 1, &light->getObject()->getComponent<Transform>()->getPosition()[0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster->getProgramID(), "ShadowMap");
	if (uniformLocation >= 0)
		glUniform1i(uniformLocation,light->getShadowInfo()->getShadowmapUnitID());
	uniformLocation = glGetUniformLocation(pass_shadowcaster->getProgramID(), "farPlane");
	if (uniformLocation >= 0)
		glUniform1f(uniformLocation, light->getShadowInfo()->cam_Shadow->getFarPlane());

	unsigned int NumIndices = mesh->getGeometry()->NF() * 3;
	glDrawArrays(GL_TRIANGLES, 0, NumIndices);
	glDisable(GL_BLEND);
}

void StaticRenderer::RenderShadow(Mesh * mesh, Transform * transform, Camera * cam)
{
	std::vector<Light*> Light_CastShadow = Renderer::getInstance()->getLight_CastShadow();
	if (Light_CastShadow.empty())
		return;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(pass_shadowcaster_ALL->getProgramID());
	glBindVertexArray(mesh->getVArrayID());
	glm::mat4 CameraMatrix = cam->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = cam->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  Zihao_M2W;
	GLint uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), "Zihao_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), "Zihao_M2W");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	std::string LM_MVP = "LightMatrix_MVP";
	std::string LP_WS = "LightPosition_WS";
	std::string SM2 = "ShadowMap2D";
	std::string SM3 = "ShadowMap3D";
	std::string FP = "farPlane";
	std::string LI = "LightIntensity";
	std::string LR = "LightRadius";
	GLint EmptyTexUnit_2D = FrameBuffer::getEmptyTexUnit();
	GLint EmptyTexUnit_3D = FrameBuffer::getEmptyTexUnit()-1;
	for (int i = 0; i < 4; ++i)
	{
		if (i > Light_CastShadow.size() - 1)
		{
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (SM2 + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform1i(uniformLocation, EmptyTexUnit_2D);
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (SM3 + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform1i(uniformLocation, EmptyTexUnit_3D);
			continue;
		
		}
		Light* light = Light_CastShadow[i];
		Camera* Lightcam = light->getShadowInfo()->cam_Shadow;
		if (Light_CastShadow[i]->getLightType() == Light::Type::Point_Light)
		{
			glm::mat4 LightMatrix_MVP = Lightcam->getProjectionMatrix() * Lightcam->getWorldToViewMatrix() *Zihao_M2W;
			glm::vec4 LightPosition_WS = glm::vec4(light->getObject()->getComponent<Transform>()->getPosition(), 1);

			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (LM_MVP + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &LightMatrix_MVP[0][0]);
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (LR + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform1f(uniformLocation, light->getRadius());
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (LP_WS + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform4fv(uniformLocation, 1, &LightPosition_WS[0]);
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (SM2 + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform1i(uniformLocation, EmptyTexUnit_2D);
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (SM3 + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform1i(uniformLocation, light->getShadowInfo()->getShadowmapUnitID());
		}
		else if (Light_CastShadow[i]->getLightType() == Light::Type::Directional)
		{
			glm::mat4 LightMatrix_MVP = Lightcam->getProjectionMatrix() * Lightcam->getDLight_Shadow_ViewMatrix() *Zihao_M2W;
			glm::vec4 LightPosition_WS = glm::vec4(light->getShadowInfo()->cam_Shadow->getVirtualCamPos(), 0);
			
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (LM_MVP + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &LightMatrix_MVP[0][0]);
			
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (LP_WS + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform4fv(uniformLocation, 1, &LightPosition_WS[0]);
			
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (SM2 + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform1i(uniformLocation, light->getShadowInfo()->getShadowmapUnitID());
			uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (SM3 + std::to_string(i)).c_str());
			if (uniformLocation >= 0)
				glUniform1i(uniformLocation, EmptyTexUnit_3D);
			
		}
		uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (FP + std::to_string(i)).c_str());
		if (uniformLocation >= 0)
			glUniform1f(uniformLocation, light->getShadowInfo()->cam_Shadow->getFarPlane());

		uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), (LI + std::to_string(i)).c_str());
		if (uniformLocation >= 0)
			glUniform1f(uniformLocation, light->getIntensity());
		
		uniformLocation = glGetUniformLocation(pass_shadowcaster_ALL->getProgramID(), "LightCount");
		if (uniformLocation >= 0)
			glUniform1i(uniformLocation,Light_CastShadow.size()> 4 ? 4 : Light_CastShadow.size());
		
	}
	unsigned int NumIndices = mesh->getGeometry()->NF() * 3;
	glDrawArrays(GL_TRIANGLES, 0, NumIndices);
	glDisable(GL_BLEND);
}

void StaticRenderer::RenderShadow_Dir(Mesh * mesh, Transform * transform, Camera * cam, Light * light)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glUseProgram(pass_shadowcaster_Dir->getProgramID());
	glBindVertexArray(mesh->getVArrayID());
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBufferID());
	glm::mat4 CameraMatrix = cam->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = cam->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  Zihao_M2W;
	Camera* Lightcam = light->getShadowInfo()->cam_Shadow;
	glm::mat4 LightMatrix_MVP = Lightcam->getProjectionMatrix() * Lightcam->getDLight_Shadow_ViewMatrix() *Zihao_M2W;
	GLint uniformLocation = glGetUniformLocation(pass_shadowcaster_Dir->getProgramID(), "Zihao_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster_Dir->getProgramID(), "Zihao_M2W");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster_Dir->getProgramID(), "LightMatrix_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &LightMatrix_MVP[0][0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster_Dir->getProgramID(), "LightPosition_WS");
	if (uniformLocation >= 0)
		glUniform3fv(uniformLocation, 1, &light->getShadowInfo()->cam_Shadow->getVirtualCamPos()[0]);
	uniformLocation = glGetUniformLocation(pass_shadowcaster_Dir->getProgramID(), "ShadowMap");
	if (uniformLocation >= 0)
		glUniform1i(uniformLocation, light->getShadowInfo()->getShadowmapUnitID());
	uniformLocation = glGetUniformLocation(pass_shadowcaster_Dir->getProgramID(), "farPlane");
	if (uniformLocation >= 0)
		glUniform1f(uniformLocation, light->getShadowInfo()->cam_Shadow->getFarPlane());

	unsigned int NumIndices = mesh->getGeometry()->NF() * 3;
	glDrawArrays(GL_TRIANGLES, 0, NumIndices);
	glDisable(GL_BLEND);
}


