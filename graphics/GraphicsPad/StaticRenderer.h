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
	void Render(Mesh* mesh,Transform* transform, Object * cam_obj);
	void Render_Shadowmap_PLight(Mesh* mesh, Transform* transform, Camera * cam_obj);
	void Render_Shadowmap_DLight(Mesh* mesh, Transform* transform, Camera * cam_obj);
	void RenderShadow(Mesh* mesh, Transform* transform, Camera * cam, Light * light);
	void RenderShadow(Mesh* mesh, Transform* transform, Camera * cam);
	void RenderShadow_Dir(Mesh* mesh, Transform* transform, Camera * cam, Light * light);

private:
	static StaticRenderer* Static_Renderer;
	Pass* pass;
	Pass* pass_shadowmap_PLight;
	Pass* pass_shadowmap_DLight;
	Pass* pass_shadowcaster;
	Pass* pass_shadowcaster_Dir;
	Pass* pass_shadowcaster_ALL;
};

