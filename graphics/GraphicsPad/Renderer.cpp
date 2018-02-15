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

	TextureManager::getInstance()->init();

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
	CurObj_Trans->setScale(glm::vec3(0.01, 0.01, 0.01));
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
	bool Loaded = geometry->LoadFromFileObj(filename);
	std::vector<cyTriMesh::TriFace> vt;
	for (int i = 0; i < geometry->NF(); ++i)
	{
		vt.push_back(geometry->FT(i));
	}
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
	//Get Obj File Path
	char *PathName = nullptr;
	const char* pathEnd = strrchr(filename, '\\');
	if (!pathEnd) pathEnd = strrchr(filename, '/');
	if (pathEnd) {
		int n = int(pathEnd - filename) + 1;
		PathName = new char[n + 1];
		strncpy(PathName, filename, n);
		PathName[n] = '\0';
	}
	
	Mesh* m = CompleteMeshWithGeo(geometry, (PathName) ? std::string(filename).substr(int(pathEnd - filename) + 1, std::string(filename).length()) : std::string(filename));
	
	//Load Material
	if (m->getGeometry()->NM())
	{
		for (int i = 0; i < m->getGeometry()->NM(); ++i)
		{
			Material* mtl = new Material(m,m->getGeometry()->M(i), PathName, m->getGeometry()->GetMaterialFirstFace(i), m->getGeometry()->GetMaterialFaceCount(i));
			MaterialArray.push_back(mtl);		
		}
	}

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

	Mesh_Renderer* mr = obj->getComponent<Mesh_Renderer>();
	mr->Fill_MT_Array(&MaterialArray);

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
	m->setVArrayID(bindvertexarray(m->getVBufferID()));
	return m;
}

GLuint Renderer::bindandfillvertexbuffer(cyTriMesh * geometry)
{
	std::vector<Vertex_data> All_ver_data;
	for (int i = 0; i < geometry->NF() * 3; ++i)
	{
		Vertex_data vtx(geometry->V(geometry->F(i/3).v[i%3]), geometry->VN(geometry->FN(i / 3).v[i % 3]), geometry->VT(geometry->FT(i / 3).v[i % 3]));
		All_ver_data.push_back(vtx);
	}

	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, All_ver_data.size() * sizeof(Vertex_data), &All_ver_data[0], GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindvertexarray(GLuint vbufferID)
{
	GLuint GeometryID;
	glGenVertexArrays(1, &GeometryID);
	glBindVertexArray(GeometryID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

	return GeometryID;
}
