#pragma once
#include <Component\Component.h>

class Mesh;

class Mesh_Filter : public Component
{
public:
	Mesh_Filter(Object* obj) :
		Component(obj)
	{
		type = Component::Type::Mesh_Filter;
	}

	void BindMesh(Mesh* ms)
	{
		mesh = ms;
	}

	Mesh* getMesh() const { return mesh; }

protected:
	Mesh* mesh;
};
