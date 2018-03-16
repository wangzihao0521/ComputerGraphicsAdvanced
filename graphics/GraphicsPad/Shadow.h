#pragma once

class FrameBuffer;
class Camera;
class Object;

class Shadow {

public:
	Shadow(Object* obj);
	~Shadow()
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

	int getShadowmapUnitID();
	void SwitchToDirectional();
	void SwitchToPointLight();
	inline void Cast_Shadow_Change() { Cast_Shadow = !Cast_Shadow; }

	bool Cast_Shadow;
	FrameBuffer* ShadowFBO;
	Camera* cam_Shadow;
	int width;
	int height;
};