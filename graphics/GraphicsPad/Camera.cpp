#include <Camera.h>
#include <glm\gtx\transform.hpp>
#include <Object.h>

const float Camera::Movement_speed = 0.1f;
const float Camera::Rotation_speed = 0.5f;

void Camera::mouse_RotateUpdate(const glm::vec2 & newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f)
	{
		oldMousePosition = newMousePosition;
		return;
	}

	TengentDir = glm::cross(ViewDir, UpDir);
	glm::mat4 rotator = glm::rotate(-mouseDelta.x * Rotation_speed, UpDir) *
		glm::rotate(-mouseDelta.y * Rotation_speed, TengentDir);

	ViewDir = glm::mat3(rotator) * ViewDir;

	oldMousePosition = newMousePosition;
}

void Camera::mouse_TranslateUpdate(const glm::vec2 & newMousePosition)
{
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f)
	{
		oldMousePosition = newMousePosition;
		return;
	}

	AddPosition(ViewDir * Movement_speed * mouseDelta.x);

	oldMousePosition = newMousePosition;
}

void Camera::CenterOnBoundingBox(glm::vec3 BoundMin, glm::vec3 BoundMax)
{
	glm::vec3 CenterPoint = (BoundMax + BoundMin).operator*= (0.5);
	float ProperDistance = glm::abs(BoundMax.z - CenterPoint.z) + 20.0;
	SetPosition(CenterPoint + glm::vec3(0, 0, ProperDistance));
	ViewDir = glm::vec3(0.0f, 0.0f, -1.0f);
	TengentDir = glm::vec3(1.0f, 0.0f, 0.0f);
}

glm::mat4 Camera::getWorldToViewMatrix()
{
	glm::vec3 Position = getPosition();
	return glm::lookAt(Position, Position + ViewDir, UpDir);
}

void Camera::move_forward()
{
	AddPosition(ViewDir * Movement_speed);
}

void Camera::move_backward()
{
	AddPosition(-ViewDir * Movement_speed);
}

void Camera::move_leftward()
{
	AddPosition(-TengentDir * Movement_speed);
}

void Camera::move_rightward()
{
	AddPosition(TengentDir * Movement_speed);
}

void Camera::move_upward()
{
	AddPosition(UpDir * Movement_speed);
}

void Camera::move_downward()
{
	AddPosition(-UpDir *Movement_speed);
}

void Camera::rotate_left()
{
	glm::mat4 rotator = glm::rotate(Rotation_speed, UpDir);
	ViewDir = glm::mat3(rotator) * ViewDir;
	TengentDir = glm::cross(ViewDir, UpDir);
}

void Camera::rotate_right()
{
	glm::mat4 rotator = glm::rotate(-Rotation_speed, UpDir);
	ViewDir = glm::mat3(rotator) * ViewDir;
	TengentDir = glm::cross(ViewDir, UpDir);
}

void Camera::rotate_up()
{
	glm::mat4 rotator = glm::rotate(Rotation_speed, TengentDir);
	ViewDir = glm::mat3(rotator) * ViewDir;
	//	if (ViewDir.z > 0)
	//		UpDir = glm::vec3(0, -1, 0);
	//	if (ViewDir.z < 0)
	//		UpDir = glm::vec3(0, 1, 0);
}

void Camera::rotate_down()
{
	glm::mat4 rotator = glm::rotate(-Rotation_speed, TengentDir);
	ViewDir = glm::mat3(rotator) * ViewDir;
	//	if (ViewDir.z > 0)
	//		UpDir = glm::vec3(0, -1, 0);
	//	if (ViewDir.z < 0)
	//		UpDir = glm::vec3(0, 1, 0);
}

glm::vec3 Camera::getPosition()
{
	class Transform* transform = object->getComponent<class Transform>();
	if (transform)
	{
		return transform->getPosition();
	}
	return glm::vec3();
}

void Camera::AddPosition(glm::vec3 shift)
{
	class Transform* transform = object->getComponent<class Transform>();
	if (transform)
	{
		transform->tranlate(shift);
	}
}

void Camera::SetPosition(glm::vec3 pos)
{
	class Transform* transform = object->getComponent<class Transform>();
	if (transform)
	{
		transform->setPosition(pos);
	}
}
