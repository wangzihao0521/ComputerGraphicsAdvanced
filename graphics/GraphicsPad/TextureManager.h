#pragma once
#include <vector>
#include "Texture.h"
#include <unordered_map>

class TextureManager {

public:
	static TextureManager* getInstance();
	void init();
	Texture* ImportTex(std::string filename);
	void Gen_MipMap(Texture* tex);
	GLfloat getMagFilter(Texture* tex);
	GLfloat getMinFilter(Texture* tex);

protected:
	static TextureManager* tex_mng;
	std::vector<Texture*> TexArray;
	std::unordered_map<Texture::Tex_Filter, GLfloat> m;

};

