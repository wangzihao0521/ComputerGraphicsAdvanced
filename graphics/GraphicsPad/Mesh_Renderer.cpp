#include "Mesh_Renderer.h"
#include "Object.h"

void Mesh_Renderer::Render(Object * cam_obj,class Light* light, GLsizei screenwidth, GLsizei screenheight)
{
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++)
	{
		Mesh* mesh = object->getComponent<class Mesh_Filter>()->getMesh();
		glBindVertexArray(mesh->getVArrayID());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIBufferID());
		unsigned int NumIndices = mesh->getGeometry()->NF() * 3;
		(*iter)->ExecuteEveryPass(object->getComponent<class Transform>(), cam_obj, light, NumIndices, screenwidth, screenheight);
	}
}
