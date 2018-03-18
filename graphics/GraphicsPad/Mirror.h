#pragma once
#include <ZihaoBehavior.h>

class Framebuffer;

class Mirror : public ZihaoBehavior
{
public:

	Mirror(Object* obj): ZihaoBehavior(obj),FBO(new FrameBuffer){}
	~Mirror();

	void Start();
	void Update();
	void onWillRenderObject();
	void ResizeEvent();

protected:
	Object* MirrorCamera;

	FrameBuffer* FBO;
};
