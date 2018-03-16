#pragma once
#include "Renderer.h"
#include <Component\Component.h>

class Object;

class ZihaoBehavior : public Component
{
public :
	ZihaoBehavior(Object* obj) : Component(obj){}
	virtual ~ZihaoBehavior() {}

	virtual void Start() {}
	virtual void onWillRenderObject() {}
	virtual void Update() {}
};