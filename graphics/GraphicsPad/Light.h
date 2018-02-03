#pragma once
#include <Component\Component.h>

class Mesh;

class Light : public Component
{

public:
	enum Type {
		Directional = 0,
		Point_Light
	};
	Light(Object* obj) : Component(obj) 
	{
		type = Component::Type::Light;
		Intensity = 1;
		LightColor = glm::vec3(1, 1, 1);
		LightType = Point_Light;
	}
	~Light() {}

	static Mesh* P_Light_Mesh;
	static Mesh* D_Light_Mesh;

protected:
	float Intensity;
	glm::vec3 LightColor;
	Type LightType;
	
};

