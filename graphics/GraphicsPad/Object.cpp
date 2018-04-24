#include "Object.h"
#include "Renderer.h"
#include "SceneObjManager.h"

const float Object::Movement_speed = 0.1f;
const float Object::Rotation_speed = 0.5f;

Object::Object(std::string objName) :
	name(objName), CurrentBoundBoxMin(glm::vec3()), CurrentBoundBoxMax(glm::vec3()), RenderQueue(2000), selected(false),hided(false),Obj_type(NORMAL),label(new ObjectLabel(this))
{
	AddComponent<Transform>();
}

Object::~Object()
{
	for (auto iter = CustomComponent_Map.begin(); iter != CustomComponent_Map.end(); ++iter)
	{
		delete iter->second;
	}
	for (auto iter = Component_Map.begin(); iter != Component_Map.end(); ++iter)
	{
		delete iter->second;
	}
	delete label;
}

void Object::Render(Object* cam_obj, Light* light)
{
	if (Is_Renderable())
		getComponent<Mesh_Renderer>()->Render(cam_obj,light);

	else if (getComponent<Light>())
	{
		if (getComponent<Light>()->getLightType() == Light::Type::Point_Light)
			StaticRenderer::getInstance()->Render(Light::P_Light_Mesh, getComponent<Transform>(), cam_obj);
		else if (getComponent<Light>()->getLightType() == Light::Type::Directional)
			StaticRenderer::getInstance()->Render(Light::D_Light_Mesh, getComponent<Transform>(), cam_obj);
	}
}

void Object::RenderShadow(Camera * cam)
{
	if (!getComponent<Mesh_Filter>() || !getComponent<Mesh_Filter>()->getMesh())
		return;
	else if (!getComponent<Mesh_Renderer>() || !getComponent<Mesh_Renderer>()->Is_shadow_receiver())
		return;
	StaticRenderer::getInstance()->RenderShadow(getComponent<Mesh_Filter>()->getMesh(), getComponent<Transform>(), cam);
}

bool Object::Is_Renderable()
{
	if (getComponent<Mesh_Filter>() && getComponent<Mesh_Filter>()->getMesh() && getComponent<Mesh_Renderer>() && hided == false)
		return true;
	return false;
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

void Object::Unselect()
{
	selected = false;
	label->SetSelected(false);
}

void Object::Select()
{
	selected = true; 
	Renderer::getInstance()->AddCurrentObject(this);
	label->SetSelected(true);
}

bool Object::IsTransformationObject()
{
	if (Obj_type == TRANSFORMATION)
		return true;
	return false;
}

bool Object::IsNormalObject()
{
	if (Obj_type == NORMAL)
		return true;
	return false;
}

void Object::setRenderQueue(GLint queue)
{
	RenderQueue = queue; 
	Renderer::getInstance()->SortObjAgain();
}


