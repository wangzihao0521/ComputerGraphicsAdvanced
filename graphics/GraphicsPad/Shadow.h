#pragma once

class FrameBuffer;
class Camera;
class Object;
class Light;

class Shadow {

public:
	Shadow(Light* light);
	~Shadow();

	void Init();
	void _Release();
	int getShadowmapUnitID();
	void SwitchToDirectional();
	void SwitchToPointLight();
	void Cast_Shadow_Change();

	bool Cast_Shadow;
	FrameBuffer* ShadowFBO;
	Camera* cam_Shadow;
	int width;
	int height;
	Light* light;
};