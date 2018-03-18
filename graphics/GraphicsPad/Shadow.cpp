#include "Shadow.h"
#include "FrameBuffer.h"
#include "Camera.h"

Shadow::Shadow(Object* obj) : Cast_Shadow(false),ShadowFBO(new FrameBuffer()),cam_Shadow(new Camera(obj)),width(4096),height(4096)
{
	ShadowFBO->PointLight_Shadow_Init(width, height);
	cam_Shadow->setAspect(1.0);
	cam_Shadow->setViewAngle(90);
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
