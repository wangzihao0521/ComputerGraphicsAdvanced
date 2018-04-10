#pragma once
#include <Component\Component.h>
#include <Material.h>



class Mesh_Renderer : public Component
{
public:

	Mesh_Renderer(Object* obj) :
		Component(obj),ShadowCaster(true),ShadowReceiver(true)
	{
		type = Component::Type::Mesh_Renderer;
	}
	~Mesh_Renderer();
	void Render(Object* cam_obj,class Light* light);
	void Fill_MT_Array(std::vector<Material*> * mat_array);
	bool No_Materials() { return MaterialArray.empty(); }
	void ReCompileAllMaterial();
	void BindMaterial(GLint index, Material* mat);
	Material* getMaterialbyIndex(int i);
	bool Is_shadow_caster() { return ShadowCaster; }
	bool Is_shadow_receiver() { return ShadowReceiver; }
	void CastShadow_Change() { ShadowCaster = !ShadowCaster; }
	void ReceiveShadow_Change() { ShadowReceiver = !ShadowReceiver; }

protected:
	std::vector<Material*> MaterialArray;

	bool ShadowCaster;
	bool ShadowReceiver;

private:
	static Pass* AmbientPass;

};
