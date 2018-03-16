#include "Texture3D.h"
#include "TextureManager.h"

Texture3D::Texture3D(GLuint TexID) : Texture("CubeMap",nullptr, TexID)
{
	for (int i = 0; i < 6; ++i)
	{
		textures[i] = nullptr;
	}
}

Texture3D::~Texture3D()
{
	for (int i = 0; i < 6; ++i)
	{
		if (textures[i])
		{
			TextureManager::getInstance()->DeleteTexture(textures[i]);
			textures[i] = nullptr;
		}
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
