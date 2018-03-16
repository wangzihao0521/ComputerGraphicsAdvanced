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
		projection_Mode(Perspective),
		DLight_Shadow_ViewMatrix(glm::mat4()),
		VirtualCamPos(glm::vec3()),
		NearPlane(0.3),
		FarPlane(100.0),
		Aspect(1.33),
		ViewAngle(60.0),
		LeftPlane(-20),
		RightPlane(20),
		TopPlane(-20),
		BotPlane(20)
	{
		type = Component::Type::Camera;
		UpdateProjectionMatrix();
	}

	glm::mat4 getWorldToViewMatrix();

	void mouse_RotateUpdate(const glm::vec2& newMousePosition);
	void mouse_TranslateUpdate(const glm::vec2& newMousePosition);

	void CenterOnBoundingBox(glm::vec3 BoundMin, glm::vec3 BoundMax);

	ProjectionMode getPJ_Mode() const
	{
		return projection_Mode;
	}

	float getFarPlane() const { return FarPlane; }

	void setPJ_Mode(ProjectionMode pjm)
	{
		projection_Mode = pjm;
	}
	void ChangePJ_Mode() 
	{
		if (projection_Mode == Perspective) projection_Mode = Orthogonal;
		else if (projection_Mode == Orthogonal) projection_Mode = Perspective;
		UpdateProjectionMatrix();
	}
	void setAspect(float aspect) { Aspect = aspect;  UpdateProjectionMatrix(); }
	void setViewAngle(float angle) { ViewAngle = angle;  UpdateProjectionMatrix();}
	void switchToFace(int i);

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
	void UpdateProjectionMatrix();
	void UpdateDLight_Shadow_ViewMatrix(glm::vec3 light_dir, glm::vec3 camPos, glm::vec3 camViewDir);
	inline void setViewDir(glm::vec3 vr);
	inline void setUpDir(glm::vec3 updir);
	inline void setFarPlane(float value);
	inline glm::vec3 getViewDir() const;
	inline glm::mat4 getProjectionMatrix() const;
	inline glm::mat4 getDLight_Shadow_ViewMatrix() const;
	inline glm::vec3 getVirtualCamPos() const;


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
	glm::mat4 ProjectionMatrix;
	glm::mat4 DLight_Shadow_ViewMatrix;
	glm::vec3 VirtualCamPos;
	float NearPlane;
	float FarPlane;
	float Aspect;
	float ViewAngle;

	float LeftPlane;
	float RightPlane;
	float TopPlane;
	float BotPlane;

private:
	glm::vec3 getPosition();
	void AddPosition(glm::vec3 shift);
	void SetPosition(glm::vec3 pos);
	
};

inline void Camera::setViewDir(glm::vec3 vr)
{
	ViewDir = vr;
}

inline void Camera::setUpDir(glm::vec3 updir)
{
	UpDir = updir;
}

inline void Camera::setFarPlane(float value)
{
	FarPlane = value;
	UpdateProjectionMatrix();
}

inline glm::vec3 Camera::getViewDir() const
{
	return ViewDir;
}

inline glm::mat4 Camera::getProjectionMatrix() const
{
	return ProjectionMatrix;
}

inline glm::mat4 Camera::getDLight_Shadow_ViewMatrix() const
{
	return DLight_Shadow_ViewMatrix;
}

inline glm::vec3 Camera::getVirtualCamPos() const
{
	return VirtualCamPos;
}
