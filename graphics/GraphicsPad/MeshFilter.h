#pragma once
#include <Component\Component.h>

class Mesh;

class Mesh_Filter : public Component
{
public:
	Mesh_Filter(Object* obj) :
		Component(obj), mesh(nullptr)
	{
		type = Component::Type::Mesh_Filter;
	}
	~Mesh_Filter() { mesh = nullptr; }

	void BindMesh(Mesh* ms)
	{
		mesh = ms;
	}

	Mesh* getMesh() const { return mesh; }

protected:
	Mesh* mesh;
};
