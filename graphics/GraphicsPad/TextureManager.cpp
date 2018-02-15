#include "TextureManager.h"




TextureManager* TextureManager::tex_mng = nullptr;

TextureManager * TextureManager::getInstance()
{
	if (tex_mng)
		return tex_mng;
	tex_mng = new TextureManager();
	return tex_mng;
}

void TextureManager::init()
{
	m[Texture::NEAREST] = GL_NEAREST;
	m[Texture::LINEAR] = GL_LINEAR;
	m[Texture::NEAREST_MIPMAP_NEAREST] = GL_NEAREST_MIPMAP_NEAREST;
	m[Texture::LINEAR_MIPMAP_NEAREST] = GL_LINEAR_MIPMAP_NEAREST;
	m[Texture::NEAREST_MIPMAP_LINEAR] = GL_NEAREST_MIPMAP_LINEAR;
	m[Texture::LINEAR_MIPMAP_LINEAR] = GL_LINEAR_MIPMAP_LINEAR;
}

Texture* TextureManager::ImportTex(std::string filename)
{
	QImage img(filename.c_str(), "PNG");
	if (img.isNull())
		return nullptr;

	QImage* texture = new QImage(QGLWidget::convertToGLFormat(img));

	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glGenerateMipmap(GL_TEXTURE_2D);

	Texture* Tex_obj = new Texture(filename, texture, TextureID);
	TexArray.push_back(Tex_obj);
	return Tex_obj;
}

void TextureManager::Gen_MipMap(Texture * tex)
{
	tex->SetIsMipMap(true);
}

GLfloat TextureManager::getMagFilter(Texture * tex)
{
	return m[tex->getTex_MagfilterMode()];
}

GLfloat TextureManager::getMinFilter(Texture * tex)
{
	return m[tex->getTex_MagfilterMode()];
}

