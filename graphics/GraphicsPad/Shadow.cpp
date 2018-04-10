#include "Shadow.h"
#include "FrameBuffer.h"
#include "Camera.h"
#include "Light.h"

Shadow::Shadow(Light* l) : Cast_Shadow(false), ShadowFBO(nullptr), cam_Shadow(nullptr), light(l),width(4096),height(4096)
{
	/*ShadowFBO->PointLight_Shadow_Init(width, height);
	cam_Shadow->setAspect(1.0);
	cam_Shadow->setViewAngle(90);*/
}

Shadow::~Shadow()
{	
	_Release();
	light = nullptr;
}

void Shadow::Init()
{
	ShadowFBO = new FrameBuffer(); 
	cam_Shadow = new Camera(light->getObject());
	if (light->getLightType() == Light::Type::Point_Light)
	{
		ShadowFBO->PointLight_Shadow_Init(width, height);
		cam_Shadow->setAspect(1.0);
		cam_Shadow->setViewAngle(90);
	}
	else
	{
		ShadowFBO->DirectLight_Shadow_Init(width, height);
		cam_Shadow->setViewAngle(30);
		cam_Shadow->setFarPlane(1000);
	}
}

void Shadow::_Release()
{
	if (ShadowFBO)
	{
		delete ShadowFBO;
		ShadowFBO = nullptr;
	}
	if (cam_Shadow)
	{
		delete cam_Shadow;
		cam_Shadow = nullptr;
	}
}

int Shadow::getShadowmapUnitID()
{
	if (ShadowFBO->DepthTexture_3D)
		return ShadowFBO->DepthTexture_3D->getTexUnitID();
	else if (ShadowFBO->DepthTexture)
		return ShadowFBO->DepthTexture->getTexUnitID();
}

void Shadow::SwitchToDirectional()
{
	GLint OldTexUnitId = ShadowFBO->DepthTexture_3D->getTexUnitID();
	ShadowFBO->DirectLight_Shadow_Change(width, height, OldTexUnitId);
	cam_Shadow->setViewAngle(30);
	cam_Shadow->setFarPlane(1000);
}

void Shadow::SwitchToPointLight()
{
	GLint OldTexUnitId = ShadowFBO->DepthTexture->getTexUnitID();
	ShadowFBO->PointLight_Shadow_Change(width, height, OldTexUnitId);
	cam_Shadow->setViewAngle(90);
	cam_Shadow->setFarPlane(100);
}

void Shadow::Cast_Shadow_Change()
{
	Cast_Shadow = !Cast_Shadow;
	if (Cast_Shadow)
	{
		Init();
	}
	else
	{
		_Release();
	}
}
