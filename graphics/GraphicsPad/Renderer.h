#pragma once
#include <Qt\qtimer.h>
#include <QtGui\qkeyevent>
#include <Object.h>

class Renderer 
{
protected:
	
	std::vector<Object*> ObjectArray;
	std::vector<Camera*> CameraArray;
	std::vector<Mesh*> MeshArray;
	std::vector<Light*> LightArray;

	Object* CurrentCamera;
	Object* CurrentObject;
	GLint CurrentLight;

	GLsizei ScreenWidth;
	GLsizei ScreenHeight;
	
public:
	Renderer() { }

	void init(GLsizei width, GLsizei height,char* argv);
	void start();
	void ReCompileALLShader();
	Mesh* ImportObj(char* filename);

	void PutMeshInScene(Mesh* mesh);
	void CreateCameraInScene(std::string name);
	Object* CreateLightInScene(std::string name);

	void SwitchToNextLight();
	Object* getCurrentCamera() const { return CurrentCamera; }
	Object* getCurrentObject() const { return CurrentObject; }
	Object* getCurrentLight()  const { return LightArray[CurrentLight]->getObject(); }


	static glm::vec3 AmbientColor;

private:
	void PushCameraInArray(Camera* cam);
	void PushLightsInArray(Light* light);
	Mesh* CompleteMeshWithGeo(cyTriMesh* geo, std::string MS_Name);
	GLuint bindandfillvertexbuffer(cyTriMesh * geometry);
	GLuint bindandfillindicesbuffer(cyTriMesh * geometry);
	GLuint bindandfillvertexNormalbuffer(cyTriMesh * geometry);
	GLuint bindandfillindicesNormalbuffer(cyTriMesh * geometry);
	GLuint bindvertexarray(GLuint vbufferID, GLuint ibufferID, GLuint vnbufferID, GLuint inbufferID);
};

