#pragma once
#include <ZihaoBehavior.h>

class KeepRotating : public ZihaoBehavior
{
public:
	KeepRotating(Object* obj) : ZihaoBehavior(obj){}
	~KeepRotating(){}

	void Start() {}
	void Update()
	{
		object->getComponent<class Transform>()->rotate(glm::vec3(0, 0.15, 0));
	}
	void onWillRenderObject() {}
};
