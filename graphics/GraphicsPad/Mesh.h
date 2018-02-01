#pragma once
#include <cyTriMesh.h>

struct Mesh {
	GLint VertexBufferID;
	GLint IndicesBufferID;
	GLint VertexArrayID;

	cyTriMesh* geometry;

	Mesh(cyTriMesh* geo = nullptr):
		VertexBufferID(0),IndicesBufferID(0), VertexArrayID(0),geometry(geo){}
};
