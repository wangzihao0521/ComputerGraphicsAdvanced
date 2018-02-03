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
		MaterialArray.push_back(Material::DefaultMaterial);
	}
	void Render(Object* cam_obj,class Light* light, GLsizei screenwidth, GLsizei screenheight);

protected:
	std::vector<Material*> MaterialArray;
};
