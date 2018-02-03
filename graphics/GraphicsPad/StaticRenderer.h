#pragma once
#include <Material.h>

class Mesh;

class StaticRenderer
{
public:
	StaticRenderer() {}

	static StaticRenderer* getInstance() 
	{
		if (Static_Renderer)
			return Static_Renderer;
		else
		{
			Static_Renderer = new StaticRenderer();
			return Static_Renderer;
		}
	}

	void init();
	void Render(Mesh* mesh,Transform* transform, Object * cam_obj, GLsizei screenwidth, GLsizei screenheight);

private:
	static StaticRenderer* Static_Renderer;
	Pass* pass;
};

