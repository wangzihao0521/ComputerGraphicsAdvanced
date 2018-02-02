#include "Object.h"


Object::Object(std::string objName)
{
	name = objName;
	MaterialArray.push_back(Material::DefaultMaterial);
	CurrentBoundBoxMin = glm::vec3();
	CurrentBoundBoxMax = glm::vec3();
	AddComponent<Transform>();
}

void Object::Render(Object* cam_obj, GLsizei screenwidth, GLsizei screenheight)
{
	if (getComponent<Mesh_Filter>())
		for (auto iter = MaterialArray.begin(); iter != MaterialArray.end(); iter++)
		{
			glBindVertexArray(getComponent<Mesh_Filter>()->getMesh()->getVArrayID());
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, getComponent<Mesh_Filter>()->getMesh()->getIBufferID());
			unsigned int NumIndices = getComponent<Mesh_Filter>()->getMesh()->getGeometry()->NF() * 3;
			(*iter)->ExecuteEveryPass(getComponent<Transform>(), cam_obj, NumIndices, screenwidth, screenheight);
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
	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), getComponent<Transform>()->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), getComponent<Transform>()->getRotation().z, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(), getComponent<Transform>()->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), getComponent<Transform>()->getRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), getComponent<Transform>()->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;

	cyPoint3f min = getComponent<Mesh_Filter>()->getMesh()->getGeometry()->GetBoundMin();
	cyPoint3f max = getComponent<Mesh_Filter>()->getMesh()->getGeometry()->GetBoundMax();
	CurrentBoundBoxMin = glm::vec3(Zihao_M2W * glm::vec4(min.x, min.y, min.z, 1) );
	CurrentBoundBoxMax = glm::vec3(Zihao_M2W * glm::vec4(max.x, max.y, max.z, 1) );
}

