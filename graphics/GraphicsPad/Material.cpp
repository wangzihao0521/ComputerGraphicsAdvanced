#include "Material.h"
#include "Object.h"
#include "FrameBuffer.h"

glm::vec3 Material::AmbientColor = glm::vec3();

Material::Material(std::string Materialname, char * Vshaderfilename, char * Fshaderfilename):
	name(Materialname), map_Ka(nullptr), map_Kd(nullptr), map_Ks(nullptr), map_Ns(nullptr), map_d(nullptr), map_bump(nullptr), map_disp(nullptr), first_face(0), face_count(0)
{
	Ka[0] = Ka[1] = Ka[2] = 0.3;
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
	name(mat.name),PathName(path_name), map_Ka(nullptr), map_Kd(nullptr), map_Ks(nullptr), map_Ns(nullptr), map_d(nullptr), map_bump(nullptr), map_disp(nullptr)
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
	first_face = firstface;
	face_count = facecount;

	Pass * p = ShaderCompiler::getInstance()->Compile("DefaultVertexShader.glsl", "DefaultFragmentShader.glsl");
	PassArray.push_back(p);
}

void Material::ExecuteEveryPass(Transform* transform, Object* cam,Light* light, GLsizei screenwidth, GLsizei screenheight)
{	
	for (auto iter = PassArray.begin(); iter != PassArray.end(); iter++)
	{
		glUseProgram((*iter)->getProgramID());
		Add_Zihao_MVP((*iter),transform,cam,screenwidth,screenheight);
		Add_Default_Parameter(*iter);
		Add_Light_Uniform(*iter,light);
		glDrawArrays(GL_TRIANGLES,first_face * 3, face_count * 3);
		
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

void Material::Bind_map_Kd_FBOTexUnit()
{
	GLint i = FrameBuffer::count - 1;
	if (!map_Kd)
		map_Kd = TextureManager::getInstance()->CreateEmptyTexture();
	map_Kd->setTexUnitId(31 - i * 2);
}

void Material::Add_Zihao_MVP(Pass* pass,Transform* transform, Object* cam, GLsizei screenwidth, GLsizei screenheight)
{
	if (!cam)
		return;
	Camera* Camera_Component = cam->getComponent<Camera>();
	if (!Camera_Component)
		return;

	glm::mat4 CameraMatrix = Camera_Component->getWorldToViewMatrix();
	
	glm::mat4 projectionMatrix = glm::mat4();
	if (Camera_Component->getPJ_Mode() == Perspective)
		projectionMatrix = glm::perspective(60.0f, ((float)screenwidth / screenheight), 0.3f, 1000.0f);
	else if (Camera_Component->getPJ_Mode() == Orthogonal)
	{
		float distance = glm::distance(transform->getPosition(), cam->getComponent<Transform>()->getPosition());
		projectionMatrix = glm::ortho(-distance / 2, distance / 2, -distance / 2, distance / 2, 1.0f, 100.0f);
	}

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix =  glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0)) *
								glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
								glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1)) ;
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix * Zihao_M2W;

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
	GLint LightPosuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_LightPosition_WS");
	if (LightPosuniformLocation >= 0)
		glUniform4fv(LightPosuniformLocation, 1, &light->getLightDirection()[0]);
	GLint AmbientColoruniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_AmbientColor");
	if (AmbientColoruniformLocation >= 0)
		glUniform3fv(AmbientColoruniformLocation, 1, &AmbientColor[0]);
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

	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_map_Ka");
	if (UniformLocation >= 0)
	{
		if (map_Ka)
		{
			BindTex_Shader(UniformLocation, Tex_Unit_number,map_Ka);
		}
		else
		{
			BindTex_Shader(UniformLocation, Tex_Unit_number, TextureManager::WHITE);
		}
	}
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_map_Kd");
	if (UniformLocation >= 0)
	{
		if (map_Kd)
		{
			if (map_Kd->getTexUnitID() < 0)
				BindTex_Shader(UniformLocation, Tex_Unit_number, map_Kd);
			else 
				glUniform1i(UniformLocation, map_Kd->getTexUnitID());
		}
		else
		{
			BindTex_Shader(UniformLocation, Tex_Unit_number, TextureManager::WHITE);
		}
	}	
	UniformLocation = glGetUniformLocation(pass->getProgramID(), "DeFt_Mtl_map_Ks");
	if (UniformLocation >= 0)
	{
		if (map_Ks)
		{
			BindTex_Shader(UniformLocation, Tex_Unit_number, map_Ks);
		}
		else
		{
			BindTex_Shader(UniformLocation, Tex_Unit_number, TextureManager::WHITE);
		}
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

