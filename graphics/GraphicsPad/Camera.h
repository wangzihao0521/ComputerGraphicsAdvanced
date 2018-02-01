#pragma once
#include <glm\glm.hpp>


enum ProjectionMode {
	Perspective = 0,
	Orthogonal = 1
};

class Camera 
{
public:
	Camera(char* CamName = "Camera1", glm::vec3 pos = glm::vec3()) :
		name(CamName),
		Position(pos),
		ViewDir(0.0f, 0.0f, -1.0f),
		UpDir(0.0f, 1.0f, 0.0f),
		TengentDir(1.0f, 0.0f, 0.0f),
		projection_Mode(Perspective)
	{}

	glm::mat4 getWorldToViewMatrix() const;

	void mouse_RotateUpdate(const glm::vec2& newMousePosition);
	void mouse_TranslateUpdate(const glm::vec2& newMousePosition);

	void CenterOnBoundingBox(glm::vec3 BoundMin, glm::vec3 BoundMax);

	glm::vec3 getPosition() const
	{
		return Position;
	}

	char* getName() const
	{
		return name;
	}

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

	void setPosition(glm::vec3 NewPosition) {
		Position = NewPosition;
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

	void operator = (const Camera cam)
	{
		//		Camera camera;
		name = cam.name;
		Position = cam.Position;
		ViewDir = cam.ViewDir;
		TengentDir = cam.TengentDir;
		//		return camera;
	}

protected:
	char* name;
	glm::vec3 Position;
	glm::vec2 oldMousePosition;
	glm::vec3 ViewDir;
	glm::vec3 UpDir;
	static const float Movement_speed;
	static const float Rotation_speed;
	glm::vec3 TengentDir;
	ProjectionMode projection_Mode;
};
