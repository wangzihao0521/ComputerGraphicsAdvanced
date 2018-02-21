#pragma once
#include <ZihaoBehavior.h>

class Framebuffer;

class Mirror : public ZihaoBehavior
{
public:

	Mirror(Object* obj): ZihaoBehavior(obj),FBO(new FrameBuffer){}

	void Start();
	void Update();
	void onWillRenderObject();

protected:
	Object* MirrorCamera;

	FrameBuffer* FBO;
};
