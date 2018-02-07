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
	Light(Object* obj);

	~Light() {}

	glm::vec4 getLightDirection();
	void setType(Type type) { LightType = type; }
	Type getLightType() const { return LightType; }

	void mouse_RotateUpdate(const glm::vec2 & newMousePosition);
	void ReComputeLightDir();
	void changeType();

	static Mesh* P_Light_Mesh;
	static Mesh* D_Light_Mesh;

protected:
	//Properties for all type of lights
	float Intensity;
	glm::vec3 LightColor;
	Type LightType;

	//Directional Light Properties
	glm::vec2 oldMousePosition;
	glm::vec4 lightDir;
	glm::vec3 TengentDir;
	
};

