#pragma once
#include <Material.h>
#include <Mesh.h>


class Object {
public:
	Object(Mesh* objMesh = nullptr, std::string objName = "object");

	Transform* getTransform() const { return transform; }
	glm::vec3 getCurrentBoundBoxMin() const { return CurrentBoundBoxMin; }
	glm::vec3 getCurrentBoundBoxMax() const { return CurrentBoundBoxMax; }

	void Render(Camera* cam, GLsizei screenwidth, GLsizei screenheight);
	void CompileAllMaterial();
	void ComputeCurrentBoundBox();

	cyTriMesh* getGeometry() const { return mesh->geometry; }
protected:
	std::string name;
	Mesh* mesh;
	Transform* transform;
	std::vector<Material*> MaterialArray;

	glm::vec3 CurrentBoundBoxMin;
	glm::vec3 CurrentBoundBoxMax;

};