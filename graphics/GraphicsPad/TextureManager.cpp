#include "TextureManager.h"

TextureManager* TextureManager::tex_mng = nullptr;
Texture* TextureManager::WHITE = nullptr;
Texture* TextureManager::BLACK = nullptr;

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

	TextureManager::WHITE = ImportTex("Default\\Texture\\white.png");
	TextureManager::BLACK = ImportTex("Default\\Texture\\black.png");
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
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width(), texture->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	Texture* Tex_obj = new Texture(filename, texture, TextureID);
	TexArray.push_back(Tex_obj);
	return Tex_obj;
}

Texture3D * TextureManager::ImportTex3D(std::string rightImage, std::string leftImage, std::string topImage, std::string bottomImage, std::string frontImage, std::string backImage)
{
	std::string TexFile[6] = { rightImage, leftImage, topImage, bottomImage, frontImage, backImage };

	GLuint TextureID;
	glGenTextures(1, &TextureID);
	Texture3D* Tex_obj = new Texture3D(TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);
	for (int i = 0; i < 6; ++i) {
//		QImage Texdata = QGLWidget::convertToGLFormat(QImage(TexFile[i].c_str(), "PNG"));
		Texture * Texdata = ImportTex(TexFile[i]);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, Texdata->getImage()->width(), Texdata->getImage()->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Texdata->getImage()->bits());
		Tex_obj->BindTexbyIndex(i, Texdata);
	}
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	

	Tex3DArray.push_back(Tex_obj);
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

Texture * TextureManager::CreateEmptyTexture()
{
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	Texture* Tex_obj = new Texture("", new QImage(), TextureID);
	TexArray.push_back(Tex_obj);
	return Tex_obj;
}

Texture3D * TextureManager::CreateEmptyTexture_3D()
{
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);

	Texture3D* Tex_obj = new Texture3D(TextureID);
	Tex3DArray.push_back(Tex_obj);
	return Tex_obj;
}

void TextureManager::DeleteTexture3D(Texture3D * tex)
{
	for (auto iter = Tex3DArray.begin(); iter != Tex3DArray.end(); ++iter)
	{
		if ((*iter) == tex)
		{
			delete tex;
			iter = Tex3DArray.erase(iter);
			return;
		}
	}
}

void TextureManager::DeleteTexture(Texture * tex)
{
	for (auto iter = TexArray.begin(); iter != TexArray.end(); ++iter)
	{
		if ((*iter) == tex)
		{
			delete tex;
			iter = TexArray.erase(iter);
			return;
		}
	}
}

