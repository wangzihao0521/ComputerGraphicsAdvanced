#pragma once
#include <Component\Component.h>
#include <Material.h>

class Mesh_Renderer : public Component
{
public:

	Mesh_Renderer(Object* obj) :
		Component(obj)
	{
		type = Component::Type::Mesh_Renderer;
	}

protected:
	std::vector<Material*> MaterialArray;
};
