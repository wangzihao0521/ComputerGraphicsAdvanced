#pragma once
#include <Mesh.h>
#include <MeshFilter.h>
#include <Transform.h>
#include <unordered_map>
#include <Mesh_Renderer.h>
#include <Light.h>
#include <StaticRenderer.h>


//class Material;

class Object {
public:
	Object(std::string objName = "object");

	glm::vec3 getCurrentBoundBoxMin() const { return CurrentBoundBoxMin; }
	glm::vec3 getCurrentBoundBoxMax() const { return CurrentBoundBoxMax; }

	void Render(Object* cam_obj,Light* light, GLsizei screenwidth, GLsizei screenheight);
	void CompileAllMaterial();
	void ComputeCurrentBoundBox();

	template <class T>
	void AddComponent();

	template <class T>
	T* getComponent();

	static const float Movement_speed;
	static const float Rotation_speed;

protected:
	std::string name;
	std::vector<Material*> MaterialArray;

	std::unordered_map<Component::Type, Component*> Component_Map;

	glm::vec3 CurrentBoundBoxMin;
	glm::vec3 CurrentBoundBoxMax;	
};

template <class T>
void Object::AddComponent()
{
	Component* p = new T(this);
	Component::Type type = p->getType();
	if (Component_Map[type] == nullptr)
	{
		Component_Map[type] = p;
		return;
	}
	else
	{
		printf("Component Already exists");
		delete p;
		return;
	}
}

template<class T>
T * Object::getComponent()
{
	Component* bp = new T(this);
	Component::Type type = bp->getType();
	T* dp = dynamic_cast<T*>(Component_Map[type]);

	if (dp) {
		return dp;
	}
//	printf("Cannot find the Component");
	return nullptr;
}
