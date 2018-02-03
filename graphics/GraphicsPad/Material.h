#pragma once
#include <vector>
#include <ShaderCompiler.h>
#include <Camera.h>
#include <glm\gtc\matrix_transform.hpp>

class Transform;
class Light;

class Material {
protected:
	std::string name;
	std::vector<Pass*> PassArray;

	
public:
	Material(std::string Materialname = "Material", char* Vshaderfilename = nullptr, char* Fshaderfilename = nullptr);
	void ExecuteEveryPass(Transform* transform, Object* cam,Light* light, unsigned int numIndices, GLsizei screenwidth, GLsizei screenheight);
	void ReCompileShaders();

	static Material* DefaultMaterial;
	static glm::vec3 AmbientColor;

private:
	void Add_Zihao_MVP(Pass* pass, Transform* transform,Object* cam, GLsizei screenwidth, GLsizei screenheight);
	void Add_Light_Uniform(Pass* pass,Light* light);
};
