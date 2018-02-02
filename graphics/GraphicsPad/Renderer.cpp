#include "Renderer.h"

void Renderer::init(GLsizei width, GLsizei height,char* filename)
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);
	ScreenWidth = width;
	ScreenHeight = height;
	CurrentObject = nullptr;

	Material::DefaultMaterial = new Material("DefaultMaterial", "DefaultVertexShader.glsl", "DefaultFragmentShader.glsl");

	CreateCameraInScene("MainCamera");
	Transform* CurCam_Trans = CurrentCamera->getComponent<Transform>();
	CurCam_Trans->setPosition(glm::vec3(0, 8.6, 31.6));

	Mesh *teapot = ImportObj(filename);
	if (!teapot)
		return;
	PutMeshInScene(teapot);
	Transform* CurObj_Trans = CurrentObject->getComponent<Transform>();
	CurObj_Trans->setRotation(glm::vec3(-90, 0, 0));
}

void Renderer::start()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, ScreenWidth, ScreenHeight);
	glEnable(GL_DEPTH_TEST);
	for (auto iter = ObjectArray.begin(); iter != ObjectArray.end(); iter++)
	{
		if (*iter)
		{
			(*iter)->Render(CurrentCamera,ScreenWidth,ScreenHeight);
		}
	}
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

void Renderer::PushCameraInArray(Camera* cam)
{
	CameraArray.push_back(cam);
}

Mesh * Renderer::CompleteMeshWithGeo(cyTriMesh * geometry, std::string MS_Name)
{
	Mesh* m = new Mesh(geometry,MS_Name);
	m->setVBufferID(bindandfillvertexbuffer(geometry));
	m->setIBufferID(bindandfillindicesbuffer(geometry));
	m->setVArrayID(bindvertexarray(m->getVBufferID(), m->getIBufferID()));
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

GLuint Renderer::bindvertexarray(GLuint vbufferID, GLuint ibufferID)
{
	GLuint GeometryID;
	glGenVertexArrays(1, &GeometryID);
	glBindVertexArray(GeometryID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibufferID);

	return GeometryID;
}
