#pragma once
#include <glm\glm.hpp>
#include <Component\Component.h>


enum ProjectionMode {
	Perspective = 0,
	Orthogonal = 1
};

class Camera : public Component
{
public:
	Camera(Object* obj) :
		Component(obj),
		ViewDir(0.0f, 0.0f, -1.0f),
		UpDir(0.0f, 1.0f, 0.0f),
		TengentDir(1.0f, 0.0f, 0.0f),
		projection_Mode(Perspective)
	{
		type = Component::Type::Camera;
	}

	glm::mat4 getWorldToViewMatrix();

	void mouse_RotateUpdate(const glm::vec2& newMousePosition);
	void mouse_TranslateUpdate(const glm::vec2& newMousePosition);

	void CenterOnBoundingBox(glm::vec3 BoundMin, glm::vec3 BoundMax);

	ProjectionMode getPJ_Mode() const
	{
		return projection_Mode;
	}

	void setPJ_Mode(ProjectionMode pjm)
	{
		projection_Mode = pjm;
	}
	void ChangePJ_Mode() 
	{
		if (projection_Mode == Perspective) projection_Mode = Orthogonal;
		else if (projection_Mode == Orthogonal) projection_Mode = Perspective;
	}

	void move_forward();
	void move_backward();
	void move_leftward();
	void move_rightward();
	void move_upward();
	void move_downward();
	void rotate_left();
	void rotate_right();
	void rotate_up();
	void rotate_down();
	inline void setViewDir(glm::vec3 vr);
	inline glm::vec3 getViewDir() const;

	void operator = (const Camera cam)
	{
		//		Camera camera;
		ViewDir = cam.ViewDir;
		TengentDir = cam.TengentDir;
		//		return camera;
	}

protected:
	glm::vec2 oldMousePosition;
	glm::vec3 ViewDir;
	glm::vec3 UpDir;
	glm::vec3 TengentDir;
	ProjectionMode projection_Mode;

private:
	glm::vec3 getPosition();
	void AddPosition(glm::vec3 shift);
	void SetPosition(glm::vec3 pos);
	
};

inline void Camera::setViewDir(glm::vec3 vr)
{
	ViewDir = vr;
}

inline glm::vec3 Camera::getViewDir() const
{
	return ViewDir;
}
