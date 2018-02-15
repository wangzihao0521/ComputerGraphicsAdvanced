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
	void Render(Object* cam_obj,class Light* light, GLsizei screenwidth, GLsizei screenheight);
	void Fill_MT_Array(std::vector<Material*> * mat_array);

protected:
	std::vector<Material*> MaterialArray;
};
