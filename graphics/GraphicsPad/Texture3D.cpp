#include "Texture3D.h"

Texture3D::Texture3D(GLuint TexID) : name("CubeTexture"), TextureID(TexID)
{
	for (int i = 0; i < 6; ++i)
	{
		textures[i] = nullptr;
	}
}


void Texture3D::BindTexbyIndex(GLint index, Texture * tex)
{
	if (textures[index])
	{
		Texture* temp = textures[index];
		textures[index] = tex;
		delete temp;
		return;
	}
	textures[index] = tex;
}
