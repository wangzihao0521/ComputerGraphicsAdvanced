#include "Mirror.h"
#include <glm\gtc\matrix_transform.hpp>


Mirror::~Mirror()
{
	if (MirrorCamera)
	{
		delete MirrorCamera;
		MirrorCamera = nullptr;
	}
	if (FBO)
	{
		delete FBO;
		FBO = nullptr;
	}
}

void Mirror::Start()
{
	MirrorCamera = new Object("MirrorCamera");
	MirrorCamera->AddComponent<class Camera>();
	FBO->init(Renderer::getInstance()->ScreenWidth, Renderer::getInstance()->ScreenHeight);
}

void Mirror::Update()
{
}

void Mirror::onWillRenderObject()
{
	class Transform* Main_cam_trans = Renderer::getMainCamera()->getComponent<class Transform>();
	class Transform* mirror_trans = object->getComponent<class Transform>();

	class Camera* Main_cam = Renderer::getMainCamera()->getComponent<class Camera>();

	float DistanceY = glm::dot(Main_cam_trans->getPosition() - mirror_trans->getPosition(), glm::vec3(0, 1, 0));
	
	MirrorCamera->getComponent<class Transform>()->setPosition(Main_cam_trans->getPosition() - 2 * DistanceY * glm::vec3(0, 1, 0));
	//MirrorCamera->getComponent<class Transform>()->setPosition(glm::vec3(Main_cam_trans->getPosition().x, Main_cam_trans->getPosition().y, Main_cam_trans->getPosition().z - 2 * DistanceZ));
	glm::vec3 Main_cam_Dir = Main_cam->getViewDir();
	MirrorCamera->getComponent<class Camera>()->setViewDir(glm::vec3(Main_cam_Dir.x, -Main_cam_Dir.y, Main_cam_Dir.z));

	Renderer::getInstance()->RenderToTexture(MirrorCamera, FBO);

	Material* mat = object->getComponent<class Mesh_Renderer>()->getMaterialbyIndex(0);

	mat->Bind_newmap_FBOTexUnit(FBO->ColorTexture);
	mat->MirrorCamMatrix = MirrorCamera->getComponent<class Camera>()->getProjectionMatrix() * MirrorCamera->getComponent<class Camera>()->getWorldToViewMatrix();


}
