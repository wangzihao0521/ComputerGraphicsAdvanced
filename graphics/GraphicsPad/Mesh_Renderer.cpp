#include "Mesh_Renderer.h"
#include "Object.h"
#include "StaticRenderer.h"

Pass* Mesh_Renderer::AmbientPass = nullptr;

Mesh_Renderer::~Mesh_Renderer()
{
	MaterialArray.clear();
	delete AmbientPass;
}

void Mesh_Renderer::Render(Object * cam_obj,class Light* light)
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5);
	int i = 0;
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++)
	{
		Mesh* mesh = object->getComponent<class Mesh_Filter>()->getMesh();
		glBindVertexArray(mesh->getVArrayID());
		cyTriMesh* geo = mesh->getGeometry();
		int firstface = geo->GetMaterialFirstFace(i);
		int facecount = geo->NM() == 0? geo->NF() : geo->GetMaterialFaceCount(i);
		(*iter)->ExecuteEveryPass(firstface,facecount,object->getComponent<class Transform>(), cam_obj, light);
		++i;
	}
	glDisable(GL_ALPHA_TEST);
}

void Mesh_Renderer::Fill_MT_Array(std::vector<Material*> * mat_array)
{
	Mesh* mesh = object->getComponent<class Mesh_Filter>()->getMesh();
	if (!mesh || !mesh->getGeometry()->NM())
	{
		Material* DefaultMaterial = new Material("DefaultMaterial", "Default\\ShaderFile\\DefaultVertexShader.glsl", "Default\\ShaderFile\\DefaultFragmentShader.glsl");
		DefaultMaterial->BindMesh(mesh);
		MaterialArray.push_back(DefaultMaterial);
		(*mat_array).push_back(DefaultMaterial);
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

void Mesh_Renderer::ReCompileAllMaterial()
{
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++)
	{
		(*iter)->ReCompileShaders();
	}
}

void Mesh_Renderer::BindMaterial(GLint index, Material * mat)
{
	Mesh* mesh = object->getComponent<class Mesh_Filter>()->getMesh();
	if (MaterialArray[index])
	{
		//Material* oldmat = MaterialArray[index];
		MaterialArray[index] = mat;
		//delete oldmat;
		return;
	}
	MaterialArray.push_back(mat);
}

Material * Mesh_Renderer::getMaterialbyIndex(int i)
{
	return MaterialArray[i];
}




