#pragma once
#include <Mesh.h>
#include <MeshFilter.h>
#include <Transform.h>
#include <unordered_map>
#include <Mesh_Renderer.h>
#include <Light.h>
#include <StaticRenderer.h>
#include <typeindex>


class ZihaoBehavior;

class Object {
public:
	Object(std::string objName = "object");

	glm::vec3 getCurrentBoundBoxMin() const { return CurrentBoundBoxMin; }
	glm::vec3 getCurrentBoundBoxMax() const { return CurrentBoundBoxMax; }

	void Render(Object* cam_obj,Light* light, GLsizei screenwidth, GLsizei screenheight);
	void CompileAllMaterial();
	void ComputeCurrentBoundBox();
	void Unselect() { selected = false; }
	void Select() { selected = true; }
	bool IsSelected() { return selected; }
	GLint getRenderQueue() const { return RenderQueue; }
	void setRenderQueue(GLint queue);

	template <class T>
	void AddComponent();

	template <class T>
	T* getComponent();

	template <class T>
	void AddCustomComponent();

	template <class T>
	T* getCustomComponent();

	static const float Movement_speed;
	static const float Rotation_speed;

	std::unordered_map<std::type_index, ZihaoBehavior*> CustomComponent_Map;

protected:
	std::string name;

	std::unordered_map<Component::Type, Component*> Component_Map;

	glm::vec3 CurrentBoundBoxMin;
	glm::vec3 CurrentBoundBoxMax;	

	bool selected;

	GLint RenderQueue;
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
		delete bp;
		return dp;
	}
//	printf("Cannot find the Component");
	return nullptr;
}

template <class T>
void Object::AddCustomComponent()
{
	ZihaoBehavior* p = new T(this);
	std::pair<std::type_index, ZihaoBehavior*> temp(typeid(T), p);
	CustomComponent_Map.insert(temp);

}

template <class T>
T* Object::getCustomComponent()
{
	if (CustomComponent_Map[typeid(T)])
	{
		return dynamic_cast<T*>(CustomComponent_Map[typeid(T)]);
	}
	printf("Cannot find the custom component");
	return nullptr;
}
