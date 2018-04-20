#pragma once
#include <Mesh.h>
#include <MeshFilter.h>
#include <Transform.h>
#include <unordered_map>
#include <Mesh_Renderer.h>
#include <Light.h>
#include <StaticRenderer.h>
#include <typeindex>
#include "ObjectLabel.h"


class ZihaoBehavior;

class Object {
public:
	enum OBJ_TYPE
	{
		NORMAL = 0,
		TRANSFORMATION
	};

	Object(std::string objName = "");
	~Object();

	glm::vec3 getCurrentBoundBoxMin() const { return CurrentBoundBoxMin; }
	glm::vec3 getCurrentBoundBoxMax() const { return CurrentBoundBoxMax; }

	void Render(Object* cam_obj,Light* light);
	void RenderShadow(Camera* cam);

	std::string getName() { return name; }
	ObjectLabel* getLabel() { return label; }
	bool Is_Renderable();
	void CompileAllMaterial();
	void ComputeCurrentBoundBox();
	void Unselect();
	void Select();
	bool IsSelected() { return selected; }

	void UnHide() { hided = false; }
	void Hide() { hided = true; }
	void Hide_Change() { hided = !hided; }
	bool IsHided() { return hided; }

	void setObjType(OBJ_TYPE type) { Obj_type = type; }
	bool IsTransformationObject();
	bool IsNormalObject();
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

	bool hided;
	bool selected;
	OBJ_TYPE Obj_type;
	ObjectLabel* label;

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
		/*if (type == Component::Type::Light)
			p->Shadow_Init();*/
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
