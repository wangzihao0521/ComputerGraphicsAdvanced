#include "Light.h"
#include "Object.h"
#include <glm\gtx\transform.hpp>

#define Dir_Light_Default_Dir glm::vec4(0.0f,0.0f,-1.0f,0.0f)
#define Dir_Light_Default_Ten glm::vec3(1.0f,0.0f,0.0f)
#define UP glm::vec3(0.0f,1.0f,0.0f)
#define X_Axis glm::vec3 (1.0f,0.0f,0.0f)
#define Z_Axis glm::vec3 (0.0f,0.0f,1.0f)

Light::Light(Object * obj) : Component(obj)
{
	type = Component::Type::Light;
	Intensity = 1;
	LightColor = glm::vec3(1, 1, 1);
	LightType = Point_Light;

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
		LightType = Point_Light;
	else if (LightType == Point_Light)
		LightType = Directional;
}
