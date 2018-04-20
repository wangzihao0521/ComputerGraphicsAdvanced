#include "Material.h"
#include "Object.h"
#include "FrameBuffer.h"
#include "MainWindow.h"
#include "Renderer.h"

glm::vec3 Material::AmbientColor = glm::vec3();

Material::Material(std::string Materialname, char * Vshaderfilename, char * Fshaderfilename):
	File(QIcon("Assets\\brick.png"), Materialname), map_Ka(nullptr), map_Kd(nullptr), map_Ks(nullptr), map_Ns(nullptr), map_d(nullptr), map_bump(nullptr), map_disp(nullptr), newmap(nullptr)
{
	Ka[0] = Ka[1] = Ka[2] = 1;
	Kd[0] = Kd[1] = Kd[2] = 1;
	Ks[0] = Ks[1] = Ks[2] = 1;
	Tf[0] = Tf[1] = Tf[2] = 0;
	Ns = 50;
	Ni = 1;
	illum = 2;

	if (Vshaderfilename && Fshaderfilename)
	{
		Pass * p = ShaderCompiler::getInstance()->Compile(Vshaderfilename, Fshaderfilename);

		if (p) {
			PassArray.push_back(p);
			return;
		}
		else {
			printf("Create Material Failed. Bind shader again please");
		}
	}
}

Material::Material(Mesh* M,cyTriMesh::Mtl & mat, char* path_name, int firstface, int facecount):
	File(QIcon("Assets\\brick.png"), std::string(mat.name)), PathName(path_name), map_Ka(nullptr), map_Kd(nullptr), map_Ks(nullptr), map_Ns(nullptr), map_d(nullptr), map_bump(nullptr), map_disp(nullptr),newmap(nullptr)
{
	for (int i = 0; i < 3; ++i)
	{
		Ka[i] = mat.Ka[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		Kd[i] = mat.Kd[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		Ks[i] = mat.Ks[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		Tf[i] = mat.Tf[i];
	}
	Ns = mat.Ns;
	Ni = mat.Ni;
	illum = mat.illum;
	if (mat.map_Ka)
		map_Ka = TextureManager::getInstance()->ImportTex((PathName+std::string(mat.map_Ka.data)).c_str());
	if (mat.map_Kd)
		map_Kd = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_Kd.data)).c_str());
	if (mat.map_Ks)
		map_Ks = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_Ks.data)).c_str());
	if (mat.map_Ns)
		map_Ns = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_Ns.data)).c_str());
	if (mat.map_d)
		map_d = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_d.data)).c_str());
	if (mat.map_bump)
		map_bump = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_bump.data)).c_str());
	if (mat.map_disp)	
		map_disp = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_disp.data)).c_str());
	mesh = M;

	Pass * p = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\DefaultVertexShader.glsl", "Default\\ShaderFile\\DefaultFragmentShader.glsl");
	PassArray.push_back(p);
}

Material::Material(Mesh * M, cyTriMesh::Mtl & mat, char * path_name):
	File(QIcon("Assets\\brick.png"), std::string(mat.name)), PathName(path_name), map_Ka(nullptr), map_Kd(nullptr), map_Ks(nullptr), map_Ns(nullptr), map_d(nullptr), map_bump(nullptr), map_disp(nullptr), newmap(nullptr)
{
		for (int i = 0; i < 3; ++i)
		{
			Ka[i] = mat.Ka[i];
		}
		for (int i = 0; i < 3; ++i)
		{
			Kd[i] = mat.Kd[i];
		}
		for (int i = 0; i < 3; ++i)
		{
			Ks[i] = mat.Ks[i];
		}
		for (int i = 0; i < 3; ++i)
		{
			Tf[i] = mat.Tf[i];
		}
		Ns = mat.Ns;
		Ni = mat.Ni;
		illum = mat.illum;
		if (mat.map_Ka)
			map_Ka = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_Ka.data)).c_str());
		if (mat.map_Kd)
			map_Kd = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_Kd.data)).c_str());
		if (mat.map_Ks)
			map_Ks = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_Ks.data)).c_str());
		if (mat.map_Ns)
			map_Ns = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_Ns.data)).c_str());
		if (mat.map_d)
			map_d = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_d.data)).c_str());
		if (mat.map_bump)
			map_bump = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_bump.data)).c_str());
		if (mat.map_disp)
			map_disp = TextureManager::getInstance()->ImportTex((PathName + std::string(mat.map_disp.data)).c_str());
		mesh = M;

		Pass * p = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\DefaultVertexShader.glsl", "Default\\ShaderFile\\DefaultFragmentShader.glsl");
		PassArray.push_back(p);
}

Material::Material(const Material & mat):
	File(QIcon("Assets\\brick.png"), mat.filename), PathName(mat.PathName), map_Ka(mat.map_Ka), map_Kd(mat.map_Kd), map_Ks(mat.map_Ks), map_Ns(mat.map_Ns), map_d(mat.map_d), map_bump(mat.map_bump), map_disp(mat.map_disp), newmap(mat.newmap)
{
	for (int i = 0; i < 3; ++i)
	{
		Ka[i] = mat.Ka[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		Kd[i] = mat.Kd[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		Ks[i] = mat.Ks[i];
	}
	for (int i = 0; i < 3; ++i)
	{
		Tf[i] = mat.Tf[i];
	}
	Ns = mat.Ns;
	Ni = mat.Ni;
	illum = mat.illum;

	mesh = mat.mesh;
	PassArray = mat.PassArray;
}

Material::~Material()
{
	_ReleaseTex(map_Ka);
	_ReleaseTex(map_Kd);
	_ReleaseTex(map_Ks);
	_ReleaseTex(map_bump);
	_ReleaseTex(map_d);
	_ReleaseTex(map_Ns);
	_ReleaseTex(map_disp);
	_ReleaseTex(newmap);
	mesh = nullptr;
	for (auto iter = PassArray.begin(); iter != PassArray.end(); ++iter)
	{
		if (*iter)
		{
			delete (*iter);
		}
	}
	PassArray.clear();
}

void Material::ExecuteEveryPass(int firstface, int facecount,Transform* transform, Object* cam,Light* light)
{	
	for (auto iter = PassArray.begin(); iter != PassArray.end(); iter++)
	{
		glUseProgram((*iter)->getProgramID());
		Add_Zihao_MVP((*iter),transform,cam,light);
		Add_Default_Parameter(*iter);
		Add_Light_Uniform(*iter,light);
		glDrawArrays(GL_TRIANGLES, firstface * 3, facecount * 3);
		
	}
}

void Material::ReCompileShaders()
{
	if (PassArray.empty())
	{
		return;
	}
	for (auto iter = PassArray.begin(); iter != PassArray.end(); iter++)
	{
		ShaderCompiler::getInstance()->ReCompile_Pass(*iter);
	}
}

void Material::Bind_newmap_FBOTexUnit(Texture * tex)
{
	newmap = tex;
}

void Material::_PutInScene(QMouseEvent* e)
{
	QPoint point_inScene = MainWindow::getInstance()->getScene()->mapFromGlobal(e->globalPos());
	Object* obj = Renderer::getInstance()->getObjectByScreenPos(glm::vec2(point_inScene.x(), point_inScene.y()));
	if (!obj)
		return;
	Mesh_Renderer* msh_renderer = obj->getComponent<Mesh_Renderer>();
	if (!msh_renderer)
		return;
	msh_renderer->BindMaterial(0,this);
}

void Material::Add_Zihao_MVP(Pass* pass,Transform* transform, Object* cam, Light* light)
{
	if (!cam)
		return;
	Camera* Camera_Component = cam->getComponent<Camera>();
	if (!Camera_Component)
		return;

	glm::mat4 CameraMatrix = Camera_Component->getWorldToViewMatrix();
	
	glm::mat4 projectionMatrix = Camera_Component->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix =  glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
								glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
								glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1)) ;
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 CamFixTransformMatrix = glm::mat4();
	if (light)
		CamFixTransformMatrix = light->getShadowInfo()->Cast_Shadow ? glm::mat4() : glm::translate(glm::mat4(), glm::vec3(0, 0, -0.0001));
	glm::mat4 Zihao_MVP = CamFixTransformMatrix * projectionMatrix * CameraMatrix * Zihao_M2W;

	GLint M2WuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_M2W");
	if (M2WuniformLocation >= 0)
		glUniformMatrix4fv(M2WuniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	GLint MVPuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_MVP");
	if (MVPuniformLocation >= 0)
		glUniformMatrix4fv(MVPuniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
	GLint ViewPosuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_ViewPosition_WS");
	if (ViewPosuniformLocation >= 0)
		glUniform3fv(ViewPosuniformLocation, 1, &cam->getComponent<Transform>()->getPosition()[0]);
	GLint ViewDiruniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_CamViewDir");
	if (ViewDiruniformLocation >= 0)
		glUniform3fv(ViewDiruniformLocation, 1, &cam->getComponent<Camera>()->getViewDir()[0]);

	//following is just for easily testing the mirror.
	GLint MirrorCamMatrixuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_MC_W2P");
	if (MirrorCamMatrixuniformLocation >= 0)
		glUniformMatrix4fv(MirrorCamMatrixuniformLocation, 1, GL_FALSE, &MirrorCamMatrix[0][0]);
}

void Material::Add_Light_Uniform(Pass * pass, Light* light)
{
	if (light)
	{
		GLint uniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_LightPosition_WS");
		if (uniformLocation >= 0)
			glUniform4fv(uniformLocation, 1, &light->getLightDirection()[0]);
		uniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_AmbientColor");
		if (uniformLocation >= 0)
			glUniform3fv(uniformLocation, 1, &AmbientColor[0]);
		uniformLocation = glGetUniformLocation(pass->getProgramID(), "LightIntensity");
		if (uniformLocation >= 0)
			glUniform1f(uniformLocation, light->getIntensity());
		uniformLocation = glGetUniformLocation(pass->getProgramID(), "LightRadius");
		if (uniformLocation >= 0)
			glUniform1f(uniformLocation, light->getRadius());
	}
	else
	{
		GLint uniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_LightPosition_WS");
		if (uniformLocation >= 0)
			glUniform4fv(uniformLocation, 1, &glm::vec3()[0]);
		uniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_AmbientColor");
		if (uniformLocation >= 0)
			glUniform3fv(uniformLocation, 1, &glm::vec3()[0]);
		uniformLocation = glGetUniformLocation(pass->getProgramID(), "LightIntensity");
		if (uniformLocation >= 0)
			glUniform1f(uniformLocation,0);
		uniformLocation = glGetUniformLocation(pass->getProgramID(), "LightRadius");
		if (uniformLocation >= 0)
			glUniform1f(uniformLocation, 1);
	}
}

void Material::Add_Default_Parameter(Pass* pass)
{
	int Tex_Unit_number = 0;
	GLint UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_Ka");
	if (UniformLocation >= 0)
		glUniform3fv(UniformLocation, 1, Ka);
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_Kd");
	if (UniformLocation >= 0)
		glUniform3fv(UniformLocation, 1, Kd);
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_Ks");
	if (UniformLocation >= 0)
		glUniform3fv(UniformLocation, 1, Ks);
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_Tf");
	if (UniformLocation >= 0)
		glUniform3fv(UniformLocation, 1, Tf);
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_Ns");
	if (UniformLocation >= 0)
		glUniform1f(UniformLocation,Ns);
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_Ni");
	if (UniformLocation >= 0)
		glUniform1f(UniformLocation, Ni);
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_illum");
	if (UniformLocation >= 0)
		glUniform1d(UniformLocation, illum);

	UniformLocation = glGetUniformLocation(pass->getProgramID(), "SkyBoxCubeMap");
	if (UniformLocation >= 0)
	{
		glUniform1i(UniformLocation, 31);
	}
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_map_Ka");
	if (UniformLocation >= 0)
	{
		FeedShader_tex(UniformLocation, Tex_Unit_number, map_Ka, TextureManager::WHITE);
	}
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_map_Kd");
	if (UniformLocation >= 0)
	{
		FeedShader_tex(UniformLocation, Tex_Unit_number, map_Kd, TextureManager::WHITE);
	}	
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_map_Ks");
	if (UniformLocation >= 0)
	{
		FeedShader_tex(UniformLocation, Tex_Unit_number, map_Ks, TextureManager::WHITE);
	}
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "newmap");
	if (UniformLocation >= 0)
	{
		FeedShader_tex(UniformLocation, Tex_Unit_number, newmap, TextureManager::BLACK);
	}
	
}

void Material::BindTex_Shader(GLint UniformLocation,int& Tex_Unit_number, Texture* map)
{
	glActiveTexture(GL_TEXTURE0 + Tex_Unit_number);
	glBindTexture(GL_TEXTURE_2D, map->getTextureID());
	if (map->IsMipMap() && !map->HaveMipMap())
	{
		glGenerateMipmap(GL_TEXTURE_2D);
		map->SetHaveMipMap(true);
	}
	glUniform1i(UniformLocation, Tex_Unit_number);
	++Tex_Unit_number;
}

void Material::FeedShader_tex(GLint UniformLocation, int & Tex_Unit_number, Texture * map, Texture* DefaultTex)
{
	if (map)
	{
		if (map->getTexUnitID() < 0)
			BindTex_Shader(UniformLocation, Tex_Unit_number, map);
		else
			glUniform1i(UniformLocation, map->getTexUnitID());
	}
	else
	{
		BindTex_Shader(UniformLocation, Tex_Unit_number, DefaultTex);
	}
	
}

void Material::_ReleaseTex(Texture*  & tex)
{
	if (tex)
	{
		TextureManager::getInstance()->DeleteTexture(tex);
		tex = nullptr;
	}
}

