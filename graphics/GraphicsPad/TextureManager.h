#pragma once
#include <vector>
#include "Texture3D.h"
#include <unordered_map>

class TextureManager {

public:
	static TextureManager* getInstance();
	void init();
	Texture* ImportTex(std::string filename);
	Texture3D* ImportTex3D(std::string rightImage, std::string leftImage, std::string topImage, std::string bottomImage, std::string frontImage, std::string backImage );
	void Gen_MipMap(Texture* tex);
	GLfloat getMagFilter(Texture* tex);
	GLfloat getMinFilter(Texture* tex);
	Texture* CreateEmptyTexture();


	static Texture* WHITE;
	static Texture* BLACK;

protected:
	static TextureManager* tex_mng;
	
	std::vector<Texture*> TexArray;
	std::vector<Texture3D*> Tex3DArray;
	std::unordered_map<Texture::Tex_Filter, GLfloat> m;


};

