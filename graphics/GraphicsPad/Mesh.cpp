#include "Mesh.h"
#include "Renderer.h"
#include "ObjPropertiesManager.h"

void Mesh::_PutInScene(QMouseEvent* e)
{
	Renderer::getInstance()->PutMeshInScene(this);
}

void Mesh::_DisplayProperties()
{
	ObjPropertiesManager::getInstance()->DisplayMesh(this);
}

void Mesh::_PutInObjProperties(QMouseEvent * e)
{
}
