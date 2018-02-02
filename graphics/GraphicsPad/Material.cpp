#include "Material.h"
#include "Object.h"

Material* Material::DefaultMaterial = nullptr;

Material::Material(std::string Materialname, char * Vshaderfilename, char * Fshaderfilename)
{
	name = Materialname;
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

void Material::ExecuteEveryPass(Transform* transform, Object* cam,unsigned int numIndices, GLsizei screenwidth, GLsizei screenheight)
{	
	for (auto iter = PassArray.begin(); iter != PassArray.end(); iter++)
	{
		glUseProgram((*iter)->getProgramID());
		Add_Zihao_MVP((*iter),transform,cam,screenwidth,screenheight);
		glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
		
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
		projectionMatrix = glm::perspective(60.0f, ((float)screenwidth / screenheight), 0.3f, 100.0f);
	else if (Camera_Component->getPJ_Mode() == Orthogonal)
	{
		float distance = glm::distance(transform->getPosition(), cam->getComponent<Transform>()->getPosition());
		projectionMatrix = glm::ortho(-distance / 2, distance / 2, -distance / 2, distance / 2, 1.0f, 100.0f);
	}

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), transform->getPosition());
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), transform->getRotation().z, glm::vec3(0, 0, 1)) *
		glm::rotate(glm::mat4(), transform->getRotation().x, glm::vec3(1, 0, 0)) *
		glm::rotate(glm::mat4(), transform->getRotation().y, glm::vec3(0, 1, 0));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), transform->getScale());
	glm::mat4 Zihao_M2W = TransformMatrix * RotationMatrix * ScaleMatrix;
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix * Zihao_M2W;

	GLint M2WuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_M2W");
	if (M2WuniformLocation >= 0)
		glUniformMatrix4fv(M2WuniformLocation, 1, GL_FALSE, &Zihao_M2W[0][0]);
	GLint MVPuniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_MVP");
	if (MVPuniformLocation >= 0)
		glUniformMatrix4fv(MVPuniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);
}

