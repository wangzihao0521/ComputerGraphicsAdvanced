#pragma once
#include <Qt\qtimer.h>
#include <QtGui\qkeyevent>
#include <Object.h>
#include <Vertex_data.h>
#include "FrameBuffer.h"

class Renderer 
{
protected:
	
	std::vector<Object*> ObjectArray;
	std::vector<Object*> ObjectInSceneArray;
	std::vector<Object*> CurrentObject;
	std::vector<Camera*> CameraArray;
	std::vector<Mesh*> MeshArray;
	std::vector<Light*> LightArray;
	std::vector<Material*>MaterialArray;

	static Object* CurrentCamera;
	static Object* MainCamera;
	GLint CurrentLight;

	static Renderer* Zihao_renderer;
	
public:
	Renderer() { }

	void init(GLsizei width, GLsizei height,char* argv);
	static Renderer* getInstance();
	void RenderToScene();
	void RenderToTexture(Object* Cam, FrameBuffer* FBO);
	void ReCompileALLShader();
	Mesh* ImportObj(char* filename);

	void PutMeshInScene(Mesh* mesh);
	void CreateCameraInScene(std::string name);
	Object* CreateLightInScene(std::string name);

	void SwitchToNextLight();
	static Object* getMainCamera() { return MainCamera; }
	static Object* getCurrentCamera() { return CurrentCamera; }
	std::vector<Object*> getCurrentObject() { return CurrentObject; }
	void ClearCurrentObject();
	void AddCurrentObject(Object* obj);
	Object* getCurrentLight()  const { return LightArray[CurrentLight]->getObject(); }
	void SortObjAgain() { RenderQueueDirty = true; }
	void SelectObjectByScreenPos(glm::vec2 pos);
	void AddCurObjectByScreenPos(glm::vec2 pos);
	void SelectObjectById(GLint id);

	GLsizei ScreenWidth;
	GLsizei ScreenHeight;

	static glm::vec3 AmbientColor;

private:
	void PushCameraInArray(Camera* cam);
	void PushLightsInArray(Light* light);
	Mesh* CompleteMeshWithGeo(cyTriMesh* geo, std::string MS_Name);
	GLuint bindandfillvertexbuffer(cyTriMesh * geometry);
	GLuint bindvertexarray(GLuint vbufferID);
	void QuickSortObjByQueue(int low, int high);
	int Partition(int low, int high);
	void RenderSelectionOutline();

	bool RenderQueueDirty;
};

