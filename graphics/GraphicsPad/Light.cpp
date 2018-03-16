#include "Light.h"
#include <glm\gtx\transform.hpp>
#include "Renderer.h"

#define Dir_Light_Default_Dir glm::vec4(0.0f,0.0f,-1.0f,0.0f)
#define Dir_Light_Default_Ten glm::vec3(1.0f,0.0f,0.0f)
#define UP glm::vec3(0.0f,1.0f,0.0f)
#define X_Axis glm::vec3 (1.0f,0.0f,0.0f)
#define Z_Axis glm::vec3 (0.0f,0.0f,1.0f)

Light::Light(Object * obj) : Component(obj),shadow(nullptr),Intensity(1), LightColor(glm::vec3(1, 1, 1)), LightType(Point_Light),radius(50.0)
{
	type = Component::Type::Light;

	class Transform* trans = object->getComponent<class Transform>();
	lightDir =	glm::rotate(glm::mat4(), trans->getRotation().y, glm::vec3(0, 1, 0)) *
				glm::rotate(glm::mat4(), trans->getRotation().x, glm::vec3(1, 0, 0)) *
				glm::rotate(glm::mat4(), trans->getRotation().z, glm::vec3(0, 0, 1)) *
				Dir_Light_Default_Dir;
	TengentDir = Dir_Light_Default_Ten;
}

glm::vec4 Light::getLightDirection()
{
	class Transform* trans = object->getComponent<class Transform>();
	if (LightType == Point_Light)
		return glm::vec4(trans->getPosition(),1);
	else if (LightType == Directional)
	{
		return lightDir;
	}
}

void Light::mouse_RotateUpdate(const glm::vec2 & newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f)
	{
		oldMousePosition = newMousePosition;
		return;
	}

	TengentDir = glm::normalize(glm::cross(glm::vec3(lightDir), UP));
	if (TengentDir.x < 0)
		TengentDir = -TengentDir;
	glm::mat4 rotator = glm::rotate(-mouseDelta.x * Object::Rotation_speed, UP) *
		glm::rotate(-mouseDelta.y * Object::Rotation_speed, TengentDir);

	class Transform* trans = object->getComponent<class Transform>();

	object->getComponent<class Transform>()->rotate(glm::vec3(mouseDelta.y * Object::Rotation_speed,-mouseDelta.x * Object::Rotation_speed,0.0));

	ReComputeLightDir();

	oldMousePosition = newMousePosition;
}

void Light::ReComputeLightDir()
{
	class Transform* trans = object->getComponent<class Transform>();
	lightDir =  glm::rotate(glm::mat4(), trans->getRotation().y, glm::vec3(0, 1, 0)) *
				glm::rotate(glm::mat4(), trans->getRotation().x, glm::vec3(1, 0, 0)) *
				glm::rotate(glm::mat4(), trans->getRotation().z, glm::vec3(0, 0, 1)) *
				Dir_Light_Default_Dir;
}

void Light::changeType()
{
	if (LightType == Directional)
	{
		LightType = Point_Light;
		shadow->SwitchToPointLight();
	}
	else if (LightType == Point_Light)
	{
		LightType = Directional;
		shadow->SwitchToDirectional();
	}
}

void Light::Shadow_Init()
{
	if (!shadow)
		shadow = new Shadow(object);
}

void Light::RenderShadowMap()
{
	if (!shadow->Cast_Shadow)
		return;
	else
	{
		
		if (LightType == Point_Light)
		{	
			glBindFramebuffer(GL_FRAMEBUFFER, shadow->ShadowFBO->id);
			glEnable(GL_DEPTH_TEST);

			glViewport(0, 0, shadow->width, shadow->height);
			for (int i = 0; i < 6; ++i)
			{
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, shadow->ShadowFBO->DepthTexture_3D->getTextureID(), 0);
				glClear(GL_DEPTH_BUFFER_BIT);
			}
			for (int i = 0; i < 6; ++i)
			{
				shadow->cam_Shadow->switchToFace(i);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, shadow->ShadowFBO->DepthTexture_3D->getTextureID(), 0);				
				Renderer::getInstance()->RenderObject_CastShadow(shadow->cam_Shadow, Point_Light);
			}
		}
		else if (LightType == Directional)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, shadow->ShadowFBO->id);
			glEnable(GL_DEPTH_TEST);

			glViewport(0, 0, shadow->width, shadow->height);
			glClear(GL_DEPTH_BUFFER_BIT);
			Object* MainCamObj = Renderer::getMainCamera();
			shadow->cam_Shadow->UpdateDLight_Shadow_ViewMatrix(glm::vec3(lightDir), MainCamObj->getComponent<class Transform>()->getPosition(), MainCamObj->getComponent<class Camera>()->getViewDir());
			Renderer::getInstance()->RenderObject_CastShadow(shadow->cam_Shadow, Directional);
		}
	}
}

void Light::AddIntensity(float value)
{
	if (Intensity + value < 0)
	{
		Intensity = 0;
		return;
	}
	Intensity += value;
}

