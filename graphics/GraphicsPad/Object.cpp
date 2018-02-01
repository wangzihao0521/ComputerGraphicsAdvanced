#include "Object.h"


Object::Object(Mesh * objMesh, std::string objName)
{
	name = objName;
	mesh = objMesh;
	transform = new Transform();
	MaterialArray.push_back(Material::DefaultMaterial);
	CurrentBoundBoxMin = glm::vec3();
	CurrentBoundBoxMax = glm::vec3();
}

void Object::Render(Camera* cam, GLsizei screenwidth, GLsizei screenheight)
{
	if (mesh)
		for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++)
		{
			glBindVertexArray(mesh->VertexArrayID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->IndicesBufferID);
			unsigned int NumIndices = mesh->geometry->NF() * 3;
			(*iter)->ExecuteEveryPass(transform, cam, NumIndices, screenwidth, screenheight);
		}
}

void Object::CompileAllMaterial()
{
	if (MaterialArray.empty())
	{
		return;
	}
	for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++)
	{
		(*iter)->ReCompileShaders();
	}
}

void Object::ComputeCurrentBoundBox()
{
	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;

	float a = getGeometry()->GetBoundMin().y;
	CurrentBoundBoxMin = glm::vec3(Zihao_M2W * glm::vec4(getGeometry()->GetBoundMin().x, getGeometry()->GetBoundMin().y, getGeometry()->GetBoundMin().z, 1) );
	CurrentBoundBoxMax = glm::vec3(Zihao_M2W * glm::vec4(getGeometry()->GetBoundMax().x, getGeometry()->GetBoundMax().y, getGeometry()->GetBoundMax().z, 1) );
}
