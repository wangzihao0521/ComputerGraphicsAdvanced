#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>

class Object;
class Mesh;
class Pass;


class VisualTransformManager
{
public:
	enum TRANSFORMATION_MODE {
		NONE = 0,
		TRANSLATION,
		ROTATION,
		SCALE
	};

	static VisualTransformManager * getInstance();

	void init();
	void Render(glm::vec3 Pos, GLint &id);
	void executeTransform(Object* PrefetchObject, glm::vec2 cursorDelta);
	Object* getObjectById(GLint id);

	static Object* X_Arrow;
	static Object* Y_Arrow;
	static Object* Z_Arrow;

protected:

	void RenderMeshes(Mesh* x_msh, Mesh* y_msh, Mesh* z_msh,glm::vec3 Pos);
	void Update_ObjTransform(glm::vec3 Pos);

	static VisualTransformManager* Manager_Ptr;
	TRANSFORMATION_MODE mode;
	Pass* pass;
	
};

