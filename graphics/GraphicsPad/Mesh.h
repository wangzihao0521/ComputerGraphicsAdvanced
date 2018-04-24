#pragma once
#include <cyTriMesh.h>
#include "File.h"

class Mesh : public File
{
protected:
//	std::string name;
	GLint VertexBufferID;
	GLint IndicesBufferID;
	GLint VertexArrayID;

	cyTriMesh* geometry;

	void _PutInScene(QMouseEvent* e);
	void _DisplayProperties();
	void _PutInObjProperties(QMouseEvent* e);
public:
	Mesh(cyTriMesh* geo = nullptr, std::string Name = "Mesh"):
		File(QIcon("Assets\\MeshIcon.png"),Name),VertexBufferID(0),IndicesBufferID(0), VertexArrayID(0),geometry(geo){}

	GLint getVBufferID() const { return VertexBufferID; }
	GLint getIBufferID() const { return IndicesBufferID; }
	GLint getVArrayID() const { return VertexArrayID; }
	cyTriMesh* getGeometry() const { return geometry; }
	std::string getName() const { return filename; }

	void setVBufferID(GLint id) { VertexBufferID = id; }
	void setIBufferID(GLint id) { IndicesBufferID = id; }
	void setVArrayID(GLint id) { VertexArrayID = id; }


};
