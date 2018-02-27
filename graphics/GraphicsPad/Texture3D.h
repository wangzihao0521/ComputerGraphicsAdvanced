#pragma once
#include "Texture.h"

class Texture3D
{
public:
	Texture3D(GLuint TexID = 0);
	void BindTexbyIndex(GLint index, Texture* tex);
	GLuint getTextureID() const { return TextureID; }

protected:
	std::string name;
	Texture* textures[6];
	GLuint TextureID;
};
