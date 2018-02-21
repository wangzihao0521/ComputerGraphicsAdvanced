#include "Object.h"
#include "Renderer.h"

const float Object::Movement_speed = 0.1f;
const float Object::Rotation_speed = 0.5f;

Object::Object(std::string objName) :
	name(objName), CurrentBoundBoxMin(glm::vec3()), CurrentBoundBoxMax(glm::vec3()), RenderQueue(2000)
{
	AddComponent<Transform>();
}

void Object::Render(Object* cam_obj, Light* light,GLsizei screenwidth, GLsizei screenheight)
{
	if (getComponent<Mesh_Filter>() && getComponent<Mesh_Renderer>())
		getComponent<Mesh_Renderer>()->Render(cam_obj,light, screenwidth, screenheight);

	else if (getComponent<Light>())
	{
		if (getComponent<Light>()->getLightType() == Light::Type::Point_Light)
			StaticRenderer::getInstance()->Render(Light::P_Light_Mesh, getComponent<Transform>(), cam_obj, screenwidth, screenheight);
		else if (getComponent<Light>()->getLightType() == Light::Type::Directional)
			StaticRenderer::getInstance()->Render(Light::D_Light_Mesh, getComponent<Transform>(), cam_obj, screenwidth, screenheight);
	}
}

void Object::CompileAllMaterial()
{
	Mesh_Renderer* mr = getComponent<Mesh_Renderer>();
	if (!mr)
	{
		return;
	}
	if (mr->No_Materials())
	{
		return;
	}
	mr->ReCompileAllMaterial();
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

void Object::setRenderQueue(GLint queue)
{
	RenderQueue = queue; 
	Renderer::getInstance()->SortObjAgain();
}

