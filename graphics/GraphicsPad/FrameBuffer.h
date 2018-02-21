#pragma once
#include "GL\glew.h"
#include "TextureManager.h"

class FrameBuffer {
protected:
	void init_ColorTexture(GLsizei width, GLsizei height);
	void init_DepthTexture(GLsizei width, GLsizei height);	

public:
	GLuint id;
	Texture* ColorTexture;
	Texture* DepthTexture;
	static GLint count;

	FrameBuffer() :
		id(0), ColorTexture(nullptr), DepthTexture(nullptr) {}

	void init(GLsizei width, GLsizei height);

};
