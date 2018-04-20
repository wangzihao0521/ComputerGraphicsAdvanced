#include "Mesh.h"
#include "Renderer.h"

void Mesh::_PutInScene(QMouseEvent* e)
{
	Renderer::getInstance()->PutMeshInScene(this);
}
