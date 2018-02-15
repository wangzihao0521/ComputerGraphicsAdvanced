#include "Mesh_Renderer.h"
#include "Object.h"

void Mesh_Renderer::Render(Object * cam_obj,class Light* light, GLsizei screenwidth, GLsizei screenheight)
{
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++)
	{
		Mesh* mesh = object->getComponent<class Mesh_Filter>()->getMesh();
		glBindVertexArray(mesh->getVArrayID());
		(*iter)->ExecuteEveryPass(object->getComponent<class Transform>(), cam_obj, light, screenwidth, screenheight);
	}
}

void Mesh_Renderer::Fill_MT_Array(std::vector<Material*> * mat_array)
{
	Mesh* mesh = object->getComponent<class Mesh_Filter>()->getMesh();
	if (!mesh || !mesh->getGeometry()->NM())
	{
		MaterialArray.push_back(Material::DefaultMaterial);
		return;
	}
	int i = 0;
	for (auto iter = mat_array->begin(); iter != mat_array->end(); ++iter)
	{		
		if ((*iter)->getMesh() == mesh)
		{
			MaterialArray.push_back(*iter);
			if (++i == mesh->getGeometry()->NM())
			{
				return;
			}
		}	
	}
	return;


}
