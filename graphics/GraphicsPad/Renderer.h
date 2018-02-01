#pragma once
#include <Qt\qtimer.h>
#include <QtGui\qkeyevent>
#include <Object.h>

class Renderer 
{
protected:
	
	std::vector<Object*> ObjectArray;
	std::vector<Camera*> CameraArray;
	Camera* CurrentCamera;
	Object* CurrentObject;

	GLsizei ScreenWidth;
	GLsizei ScreenHeight;

	Object* teapot;

public:
	Renderer() { }

	void init(GLsizei width, GLsizei height,char* argv);
	void start();
	void ReCompileALLShader();
	Object* ImportObj(char* filename);
	void CreateObjectInScene(Object* obj);
	Camera* getCurrentCamera() const { return CurrentCamera; }
	Object* getCurrentObject() const { return CurrentObject; }

private:
	void PushCameraInArray(Camera* cam);
	Mesh* CompleteMeshWithGeo(cyTriMesh* geo);
	GLuint bindandfillvertexbuffer(cyTriMesh * geometry);
	GLuint bindandfillindicesbuffer(cyTriMesh * geometry);
	GLuint bindvertexarray(GLuint vbufferID, GLuint ibufferID);
};

