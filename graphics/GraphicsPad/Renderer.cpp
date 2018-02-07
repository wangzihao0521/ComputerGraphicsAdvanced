#include "Renderer.h"

Mesh* Light::D_Light_Mesh = nullptr;
Mesh* Light::P_Light_Mesh = nullptr;
glm::vec3 Renderer::AmbientColor = glm::vec3(0.1, 0.1, 0.1);

void Renderer::init(GLsizei width, GLsizei height,char* filename)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	ScreenWidth = width;
	ScreenHeight = height;
	CurrentObject = nullptr;
	CurrentLight = 0;

	Material::DefaultMaterial = new Material("DefaultMaterial", "DefaultVertexShader.glsl", "DefaultFragmentShader.glsl");
	StaticRenderer::getInstance()->init();

	CreateCameraInScene("MainCamera");
	Transform* CurCam_Trans = CurrentCamera->getComponent<Transform>();
	CurCam_Trans->setPosition(glm::vec3(0, 8.6, 31.6));

	Light::P_Light_Mesh = ImportObj("light_bulb.obj");
	Light::D_Light_Mesh = ImportObj("Directional_light.obj");

	Object* Light1 = CreateLightInScene("Light1");
	Light1->getComponent<Transform>()->setPosition(glm::vec3(15.0, 15.0, 0.0));

	Object* Light2 = CreateLightInScene("Light2");
	Light2->getComponent<Transform>()->setPosition(glm::vec3(-15.0, 15.0, 0.0));
//	Light2->getComponent<Transform>()->rotate(glm::vec3 (-65.0,0.0,0.0));
	Light2->getComponent<Light>()->setType(Light::Type::Directional);

	Material::AmbientColor = AmbientColor;

	Mesh *teapot = ImportObj(filename);
	if (!teapot)
		return;
	PutMeshInScene(teapot);
	Transform* CurObj_Trans = CurrentObject->getComponent<Transform>();
	CurObj_Trans->setRotation(glm::vec3(-90, 0, 0));
//	CurrentObject->AddComponent<Light>();
//	CurrentObject->getComponent<Light>()->setType(Light::Type::Directional);
//	PushLightsInArray(CurrentObject->getComponent<Light>());
}

void Renderer::start()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, ScreenWidth, ScreenHeight);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
//	std::vector<Light*> All_Lights_In_Scene;
//	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
//	{
//		if ((*iter)->getComponent<Light>())
//		{
//			All_Lights_In_Scene.push_back((*iter)->getComponent<Light>());
//		}
//	}
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		for (auto Light_iter = LightArray.begin(); Light_iter != LightArray.end(); Light_iter++)
		{
			(*iter)->Render(CurrentCamera, (*Light_iter), ScreenWidth, ScreenHeight);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
		}
		glDisable(GL_BLEND);
	}
//	All_Lights_In_Scene.clear();
	
	
}

void Renderer::ReCompileALLShader()
{
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		if (*iter)
		{
			(*iter)->CompileAllMaterial();
		}
	}
}

Mesh * Renderer::ImportObj(char * filename)
{
	if (!filename)
	{
		return nullptr;
	}
	cyTriMesh* geometry = new cyTriMesh();
	bool Loaded = geometry->LoadFromFileObj(filename,false);
	if (!Loaded)
	{
		printf("File Import Failed");
		return nullptr;
	}
	geometry->ComputeBoundingBox();
	if (!geometry->IsBoundBoxReady())
	{
		printf("BoundBox Generate Failed");
	}
	
	Mesh* m = CompleteMeshWithGeo(geometry,std::string(filename));
	MeshArray.push_back(m);
	return m;
}

void Renderer::PutMeshInScene(Mesh* mesh)
{
	if (!mesh)
		return;
	std::string MS_Name = mesh->getName();
	Object* obj = new Object(MS_Name.substr(0,MS_Name.find(".")));
	obj->AddComponent<Mesh_Filter>();
	obj->AddComponent<Mesh_Renderer>();
	Mesh_Filter* mf = obj->getComponent<Mesh_Filter>();
	mf->BindMesh(mesh);
	ObjectArray.push_back(obj);
	CurrentObject = obj;
}

void Renderer::CreateCameraInScene(std::string name)
{
	Object* obj = new Object(name);
	obj->AddComponent<Camera>();
	ObjectArray.push_back(obj);
	CurrentCamera = obj;
}

Object* Renderer::CreateLightInScene(std::string name)
{
	Object* obj = new Object(name);
	obj->AddComponent<Light>();
	ObjectArray.push_back(obj);
	PushLightsInArray(obj->getComponent<Light>());
	return obj;
}

void Renderer::SwitchToNextLight()
{
	if (CurrentLight == LightArray.size() - 1)
		CurrentLight = 0;
	else
		CurrentLight++;
}

void Renderer::PushCameraInArray(Camera* cam)
{
	CameraArray.push_back(cam);
}

void Renderer::PushLightsInArray(Light * light)
{
	LightArray.push_back(light);
}

Mesh * Renderer::CompleteMeshWithGeo(cyTriMesh * geometry, std::string MS_Name)
{
	Mesh* m = new Mesh(geometry,MS_Name);
	m->setVBufferID(bindandfillvertexbuffer(geometry));
	m->setIBufferID(bindandfillindicesbuffer(geometry));
	GLuint vnBufferId = bindandfillvertexNormalbuffer(geometry);
	GLuint inBufferId = bindandfillindicesNormalbuffer(geometry);
	m->setVArrayID(bindvertexarray(m->getVBufferID(), m->getIBufferID(),vnBufferId,inBufferId));
	return m;
}

GLuint Renderer::bindandfillvertexbuffer(cyTriMesh * geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, geometry->VertexBufferSize(), geometry->getVertexptr(), GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindandfillindicesbuffer(cyTriMesh * geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->IndicesBufferSize(), geometry->getIndicesptr(), GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindandfillvertexNormalbuffer(cyTriMesh * geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, geometry->VertexNormal_BufferSize(), geometry->get_VertexNormal_ptr(), GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindandfillindicesNormalbuffer(cyTriMesh * geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry->IndicesNormal_BufferSize(), geometry->get_IndicesNormal_ptr(), GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindvertexarray(GLuint vbufferID, GLuint ibufferID, GLuint vnbufferID, GLuint inbufferID)
{
	GLuint GeometryID;
	glGenVertexArrays(1, &GeometryID);
	glBindVertexArray(GeometryID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibufferID);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vnbufferID);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, inbufferID);

	return GeometryID;
}
