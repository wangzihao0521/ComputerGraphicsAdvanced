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
	bool No_Materials() { return MaterialArray.empty(); }
	void ReCompileAllMaterial();
	void BindMaterial(GLint index, Material* mat);
	Material* getMaterialbyIndex(int i);

protected:
	std::vector<Material*> MaterialArray;
};
