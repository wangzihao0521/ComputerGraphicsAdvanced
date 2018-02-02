#pragma once

class Object;

class Component {

public:

	enum Type {
		Text = 0,
		Transform,
		Mesh_Filter,
		Mesh_Renderer,
		Light,
		Camera,
		NonType
	};
	
	virtual ~Component(){}

	Type getType() const { return type; }

protected:
	Component(Object* obj, Type typ = NonType) :
		object(obj), type(typ) {}
	Object* object;
	Type type;

};