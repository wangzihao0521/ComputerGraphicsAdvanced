#pragma once
#include <GL\glew.h>
#include <QtOpenGL\qglwidget>
#include "File.h"

class Texture {
public:
	enum Tex_Filter {
		NEAREST = 0,
		LINEAR,
		NEAREST_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST,
		LINEAR_MIPMAP_LINEAR

	};
protected:

	std::string filename;
	QImage* img;
	GLuint TextureID;
	GLint TexUnitID;

	bool Is_MipMap;
	bool Have_MipMap;
	Tex_Filter Mag_filter;
	Tex_Filter Min_filter;

public:
	Texture(std::string file_name, QImage* image, GLuint textureID) :
		filename(file_name), img(image), TextureID(textureID), TexUnitID(-1),Is_MipMap(false), Have_MipMap(false), Mag_filter(LINEAR), Min_filter(LINEAR) {};
	~Texture() {
		if (img)
		{
			delete img;
			img = nullptr;
		}
	}
//	std::string getName() const { return name; }
	std::string getFileName() const { return filename; }
	QImage* getImage() const { return img; }
	GLuint getTextureID() const { return TextureID; }
	GLint getTexUnitID() const { return TexUnitID; }
	void setTexUnitId(GLint i) { TexUnitID = i; }
	void SetIsMipMap(bool b) { Is_MipMap = b; }
	void SetHaveMipMap(bool b) { Have_MipMap = b; }
	bool IsMipMap() {return Is_MipMap; }
	bool HaveMipMap() { return Have_MipMap; }
	Tex_Filter getTex_MagfilterMode() const { return Mag_filter; }
	Tex_Filter getTex_MinfilterMode() const { return Min_filter; }
	
};