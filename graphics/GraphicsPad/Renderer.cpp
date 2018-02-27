#include "Renderer.h"
#include "Mirror.h"
#include "SkyBox.h"
#include "SelectionManager.h"

Renderer* Renderer::Zihao_renderer = nullptr;
Mesh* Light::D_Light_Mesh = nullptr;
Mesh* Light::P_Light_Mesh = nullptr;
Object* Renderer::CurrentCamera = nullptr;
Object* Renderer::MainCamera = nullptr;
glm::vec3 Renderer::AmbientColor = glm::vec3(0.3, 0.3, 0.3);

void Renderer::init(GLsizei width, GLsizei height,char* filename)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	glCullFace(GL_BACK);
	ScreenWidth = width;
	ScreenHeight = height;
	CurrentLight = 0;
	RenderQueueDirty = true;

	TextureManager::getInstance()->init();
	StaticRenderer::getInstance()->init();
	SkyBox::getInstance()->init();
	SelectionManager::getInstance()->init();
	CreateCameraInScene("MainCamera");
	MainCamera = CurrentCamera;
	Transform* CurCam_Trans = CurrentCamera->getComponent<Transform>();
	CurCam_Trans->setPosition(glm::vec3(0, 3.3, 35.6));

	Light::P_Light_Mesh = ImportObj("light_bulb.obj");
	Light::D_Light_Mesh = ImportObj("Directional_light.obj");

	Object* Light1 = CreateLightInScene("Light1");
	Light1->getComponent<Transform>()->setPosition(glm::vec3(-15.0, 5.0, 3.0));

//	Object* Light2 = CreateLightInScene("Light2");
//	Light2->getComponent<Transform>()->setPosition(glm::vec3(-15.0, 15.0, 0.0));
////	Light2->getComponent<Transform>()->rotate(glm::vec3 (-65.0,0.0,0.0));
////	Light2->getComponent<Light>()->setType(Light::Type::Directional);

	Material::AmbientColor = AmbientColor;

	Mesh * mirror = ImportObj("Assets\\mirror.obj");
	if (!mirror)
		return;
	PutMeshInScene(mirror);
	Transform* CurObj_Trans = CurrentObject[0]->getComponent<Transform>();
	CurObj_Trans->setScale(glm::vec3(2.8, 5, 1));
	CurObj_Trans->setPosition(glm::vec3(0, 0, 0));
	CurObj_Trans->setRotation(glm::vec3(-90, 0, 0));
//	CurObj_Trans->setRotation(glm::vec3(0, 180, 0));
	CurrentObject[0]->setRenderQueue(3000);
	CurrentObject[0]->AddCustomComponent<Mirror>();
	CurrentObject[0]->getCustomComponent<Mirror>()->Start();
	Material* M_mirror = new Material("M_Mirror", "MirrorVertexShader.glsl", "MirrorFragmentShader.glsl");
	CurrentObject[0]->getComponent<Mesh_Renderer>()->BindMaterial(0, M_mirror);

	Mesh *teapot = ImportObj("Assets\\teapot.obj");
	if (!teapot)
		return;
	PutMeshInScene(teapot);
	CurObj_Trans = CurrentObject[0]->getComponent<Transform>();
	CurObj_Trans->setRotation(glm::vec3(-90, 0, 0));
	CurObj_Trans->setPosition(glm::vec3(0, 0, 0));
	CurObj_Trans->setScale(glm::vec3(0.65, 0.65, 0.65));
	Material* teapotRFL = new Material("M_Mirror", "MirrorVertexShader.glsl", "MirrorFragmentShader.glsl");
	CurrentObject[0]->getComponent<Mesh_Renderer>()->BindMaterial(0, teapotRFL);
	//	CurObj_Trans->setScale(glm::vec3(0.01, 0.01, 0.01));
	//	CurrentObject->AddComponent<Light>();
	//	CurrentObject->getComponent<Light>()->setType(Light::Type::Directional);
	//	PushLightsInArray(CurrentObject->getComponent<Light>());

	ClearCurrentObject();
}

Renderer * Renderer::getInstance()
{
	if (Zihao_renderer)
		return Zihao_renderer;
	Zihao_renderer = new Renderer();
	return Zihao_renderer;
}

void Renderer::RenderToScene()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, ScreenWidth, ScreenHeight);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	if (RenderQueueDirty)
	{
		QuickSortObjByQueue(0, ObjectArray.size()-1);
		RenderQueueDirty = false;
	}
	SkyBox::getInstance()->Render(MainCamera,ScreenWidth,ScreenHeight);
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		for (auto behavior_iter = (*iter)->CustomComponent_Map.begin(); behavior_iter != (*iter)->CustomComponent_Map.end(); ++behavior_iter)
		{
			behavior_iter->second->onWillRenderObject();
		}
		for (auto Light_iter = LightArray.begin(); Light_iter != LightArray.end(); Light_iter++)
		{
			(*iter)->Render(MainCamera, (*Light_iter), ScreenWidth, ScreenHeight);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
		}
		glDisable(GL_BLEND);
		ObjectInSceneArray.push_back(*iter);
	}
	RenderSelectionOutline();
	ObjectInSceneArray.clear();
	
}

void Renderer::RenderToTexture(Object * Cam, FrameBuffer * FBO)
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO->id);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	for (auto iter = ObjectInSceneArray.begin(); iter != ObjectInSceneArray.end(); iter++)
	{
		for (auto Light_iter = LightArray.begin(); Light_iter != LightArray.end(); Light_iter++)
		{
			(*iter)->Render(Cam, (*Light_iter), ScreenWidth, ScreenHeight);
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
		}
		glDisable(GL_BLEND);
	}
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
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
	RenderQueueDirty = true;
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
	CurrentObject.clear();
	CurrentObject.push_back(obj);
	RenderQueueDirty = true;
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

void Renderer::ClearCurrentObject()
{
	for (auto iter = CurrentObject.begin(); iter != CurrentObject.end(); ++iter)
	{
		(*iter)->Unselect();
	}
	CurrentObject.clear();
}

void Renderer::AddCurrentObject(Object * obj)
{
	CurrentObject.push_back(obj);
	obj->Select();
}

void Renderer::SelectObjectByScreenPos(glm::vec2 pos)
{
	glm::vec2 ClipPos = glm::vec2(pos.x / ScreenWidth * 2 - 1, (1 - pos.y / ScreenHeight) * 2 - 1);
	SelectionManager::getInstance()->UpdateSelectionMatrix(ScreenWidth, ScreenHeight, ClipPos);
	glUseProgram(SelectionManager::getInstance()->getSelectionPass()->getProgramID());
	glBindFramebuffer(GL_FRAMEBUFFER, SelectionManager::getInstance()->getFBO()->id);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	GLint	i = 1;
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{	
		SelectionManager::getInstance()->SelectionRender((*iter), MainCamera, ScreenWidth, ScreenHeight, i);
		++i;
	}
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	GLint data = -1;
	glReadPixels(0, 0, 1, 1, GL_RED_INTEGER, GL_INT, &data);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	if (data <= 0)
	{
		ClearCurrentObject();
		return;
	}
	SelectObjectById(data);
}

void Renderer::AddCurObjectByScreenPos(glm::vec2 pos)
{
	glm::vec2 ClipPos = glm::vec2(pos.x / ScreenWidth * 2 - 1, (1 - pos.y / ScreenHeight) * 2 - 1);
	SelectionManager::getInstance()->UpdateSelectionMatrix(ScreenWidth, ScreenHeight, ClipPos);
	glUseProgram(SelectionManager::getInstance()->getSelectionPass()->getProgramID());
	glBindFramebuffer(GL_FRAMEBUFFER, SelectionManager::getInstance()->getFBO()->id);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	GLint	i = 1;
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		SelectionManager::getInstance()->SelectionRender((*iter), MainCamera, ScreenWidth, ScreenHeight, i);
		++i;
	}
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	GLint ObjectID = -1;
	glReadPixels(0, 0, 1, 1, GL_RED_INTEGER, GL_INT, &ObjectID);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	if (ObjectID <= 0)
		return;
	AddCurrentObject(ObjectArray[ObjectID - 1]);
}

void Renderer::SelectObjectById(GLint id)
{
	ClearCurrentObject();
	AddCurrentObject(ObjectArray[id - 1]);
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

void Renderer::QuickSortObjByQueue(int low, int high)
{
	if (low < high)
	{
		int q = Partition(low, high);
		QuickSortObjByQueue(low, q - 1);
		QuickSortObjByQueue(q + 1, high);
	}
}

int Renderer::Partition(int low, int high)
{
	Object* x = ObjectArray[high];
	int i = low - 1;
	for (int j = low; j < high; ++j)
	{
		if (ObjectArray[j]->getRenderQueue() < x->getRenderQueue())
		{
			i++;
			Object* temp = ObjectArray[i];
			ObjectArray[i] = ObjectArray[j];
			ObjectArray[j] = temp;
		}
	}
	ObjectArray[high] = ObjectArray[i + 1];
	ObjectArray[i + 1] = x;

	return i + 1;
}

void Renderer::RenderSelectionOutline()
{
	if (CurrentObject.empty())
		return;
//	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_ONE, GL_ONE);
	glUseProgram(SelectionManager::getInstance()->getOutlinePass()->getProgramID());
	for (auto iter = CurrentObject.begin(); iter != CurrentObject.end(); ++iter)
	{
		SelectionManager::getInstance()->SelectionRender((*iter), MainCamera, ScreenWidth, ScreenHeight, 0);
	}
	glDisable(GL_BLEND);
}
