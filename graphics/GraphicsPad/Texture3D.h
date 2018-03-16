#pragma once
#include "Texture.h"

class Texture3D : public Texture
{
public:
	Texture3D(GLuint TexID = 0);
	~Texture3D();
	void BindTexbyIndex(GLint index, Texture* tex);
	GLuint getTextureID() const { return TextureID; }

protected:
	Texture* textures[6];
};
