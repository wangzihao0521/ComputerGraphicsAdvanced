#pragma once
#include "ShaderCompiler.h"
#include "glm\glm.hpp"

class FrameBuffer;
class Object;

class SelectionManager {
public:
	void init();
	static SelectionManager* getInstance();
	Pass* getSelectionPass() const;
	Pass* getOutlinePass() const;
	FrameBuffer* getFBO() const;
	void UpdateSelectionMatrix(GLsizei width, GLsizei height, glm::vec2 ClipPos);
	void SelectionRender(Object * obj, Object * cam_obj, GLsizei screenwidth, GLsizei screenheight,GLint id);

protected:

	float SelectRadius;
	Pass * SelectionPass;
	Pass * OutlinePass;
	glm::mat4 SelectionMatrix;
	static SelectionManager* SltManager;
	FrameBuffer* FBO;
};