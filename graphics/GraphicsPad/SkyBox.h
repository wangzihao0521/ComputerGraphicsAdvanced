#pragma once
#include "Vertex_data.h"
#include "TextureManager.h"

class Pass;
class Object;

class SkyBox 
{
public:

	void init();
	void Render(Object* cam, GLsizei screenwidth, GLsizei screenheight);
	static SkyBox* getInstance();

protected:

	static SkyBox* skybox;
	Vertex_data vertices[6];
	Texture3D * cubemap;

	GLuint bufferID;
	GLuint GeometryID;
	Pass* pass;

};