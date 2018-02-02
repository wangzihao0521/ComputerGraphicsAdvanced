#pragma once
#include <cyTriMesh.h>

class Mesh
{
protected:
	std::string name;
	GLint VertexBufferID;
	GLint IndicesBufferID;
	GLint VertexArrayID;

	cyTriMesh* geometry;
public:
	Mesh(cyTriMesh* geo = nullptr,std::string Name = "Mesh"):
		name(Name),VertexBufferID(0),IndicesBufferID(0), VertexArrayID(0),geometry(geo){}

	GLint getVBufferID() const { return VertexBufferID; }
	GLint getIBufferID() const { return IndicesBufferID; }
	GLint getVArrayID() const { return VertexArrayID; }
	cyTriMesh* getGeometry() const { return geometry; }
	std::string getName() const { return name; }

	void setVBufferID(GLint id) { VertexBufferID = id; }
	void setIBufferID(GLint id) { IndicesBufferID = id; }
	void setVArrayID(GLint id) { VertexArrayID = id; }
};
