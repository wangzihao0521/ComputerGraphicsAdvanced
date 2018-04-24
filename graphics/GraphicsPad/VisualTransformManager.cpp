#include "VisualTransformManager.h"
#include "Renderer.h"
#include "SelectionManager.h"

VisualTransformManager* VisualTransformManager::Manager_Ptr = nullptr;
Object* VisualTransformManager::X_Arrow = nullptr;
Object* VisualTransformManager::Y_Arrow = nullptr;
Object* VisualTransformManager::Z_Arrow = nullptr;

VisualTransformManager * VisualTransformManager::getInstance()
{
	if (Manager_Ptr)
		return Manager_Ptr;
	Manager_Ptr = new VisualTransformManager();
	return Manager_Ptr;
}

void VisualTransformManager::init()
{
	Mesh* X_Mesh = Renderer::getInstance()->ImportObj("Default\\Mesh\\X_Arrow.obj");
	Mesh* Y_Mesh = Renderer::getInstance()->ImportObj("Default\\Mesh\\Y_Arrow.obj");
	Mesh* Z_Mesh = Renderer::getInstance()->ImportObj("Default\\Mesh\\Z_Arrow.obj");

	X_Arrow = new Object();
	X_Arrow->AddComponent<Mesh_Filter>();
	X_Arrow->getComponent<Mesh_Filter>()->BindMesh(X_Mesh);
	X_Arrow->setObjType(Object::OBJ_TYPE::TRANSFORMATION);
	Y_Arrow = new Object();
	Y_Arrow->AddComponent<Mesh_Filter>();
	Y_Arrow->getComponent<Mesh_Filter>()->BindMesh(Y_Mesh);
	Y_Arrow->setObjType(Object::OBJ_TYPE::TRANSFORMATION);
	Z_Arrow = new Object();
	Z_Arrow->AddComponent<Mesh_Filter>();
	Z_Arrow->getComponent<Mesh_Filter>()->BindMesh(Z_Mesh);
	Z_Arrow->setObjType(Object::OBJ_TYPE::TRANSFORMATION);

	pass = ShaderCompiler::getInstance()->Compile("Default\\ShaderFile\\PureColorVertexShader.glsl", "Default\\ShaderFile\\PureColorFragmentShader.glsl");

	mode = TRANSLATION;


}

void VisualTransformManager::Render(glm::vec3 Pos, GLint &id)
{
	switch (mode)
	{
	case NONE:
		return;
	case TRANSLATION:
	{
		if (id > 0)
		{
			SelectionManager::getInstance()->SelectionRender(X_Arrow, Renderer::getMainCamera(), Renderer::getInstance()->ScreenWidth, Renderer::getInstance()->ScreenHeight, id++);
			SelectionManager::getInstance()->SelectionRender(Y_Arrow, Renderer::getMainCamera(), Renderer::getInstance()->ScreenWidth, Renderer::getInstance()->ScreenHeight, id++);
			SelectionManager::getInstance()->SelectionRender(Z_Arrow, Renderer::getMainCamera(), Renderer::getInstance()->ScreenWidth, Renderer::getInstance()->ScreenHeight, id++);
		}
		else
			RenderMeshes(X_Arrow->getComponent<Mesh_Filter>()->getMesh(), Y_Arrow->getComponent<Mesh_Filter>()->getMesh(), Z_Arrow->getComponent<Mesh_Filter>()->getMesh(), Pos);
		break;
	}
	case ROTATION:
	{

		break;
	}
	case SCALE:
	{

		break;
	}
	default:
		break;
	}
}

void VisualTransformManager::executeTransform(Object * PrefetchObject, glm::vec2 cursorDelta)
{
	Camera * Camera_Component = Renderer::getMainCamera()->getComponent<Camera>();
	if (!Camera_Component)
		return;
	glm::mat4 projectionMatrix = Camera_Component->getProjectionMatrix();
	switch (mode)
	{
	case NONE:
		return;
	case TRANSLATION:
	{
		glm::vec3 cam_viewDir = Camera_Component->getViewDir();
		float X_Weight = glm::abs(glm::dot(cam_viewDir, glm::vec3(0, 0, 1)));
		float Z_Weight = glm::abs(glm::dot(cam_viewDir, glm::vec3(1, 0, 0)));
		if (PrefetchObject == X_Arrow)
		{
			glm::vec4 Trans_Delta_WS = glm::inverse(projectionMatrix * Camera_Component->getWorldToViewMatrix()) * glm::vec4(cursorDelta.x / Renderer::getInstance()->ScreenWidth * glm::dot((X_Arrow->getComponent<Transform>()->getPosition() - Renderer::getMainCamera()->getComponent<Transform>()->getPosition()), cam_viewDir)* 2,0,0, 0);
			if (Trans_Delta_WS.x >0)
				Renderer::getInstance()->CurObjectTranslate_X(Trans_Delta_WS.x * X_Weight + glm::abs(Trans_Delta_WS.z * Z_Weight));
			else if (Trans_Delta_WS.x <0)
				Renderer::getInstance()->CurObjectTranslate_X(Trans_Delta_WS.x * X_Weight - glm::abs(Trans_Delta_WS.z * Z_Weight));
			else 
			{
				if (cam_viewDir.x > 0)
					Renderer::getInstance()->CurObjectTranslate_Z(Trans_Delta_WS.z * Z_Weight);
				else
					Renderer::getInstance()->CurObjectTranslate_Z(-Trans_Delta_WS.z * Z_Weight);
			}
		}
		if (PrefetchObject == Y_Arrow)
		{
			glm::vec4 Trans_Delta_WS = glm::inverse(projectionMatrix * Camera_Component->getWorldToViewMatrix()) * glm::vec4(0, cursorDelta.y / Renderer::getInstance()->ScreenHeight *glm::dot((Y_Arrow->getComponent<Transform>()->getPosition() - Renderer::getMainCamera()->getComponent<Transform>()->getPosition()), cam_viewDir) * 2, 0, 0);
			Renderer::getInstance()->CurObjectTranslate_Y(-Trans_Delta_WS.y);
		}
		if (PrefetchObject == Z_Arrow)
		{
			glm::vec4 Trans_Delta_WS = glm::inverse(projectionMatrix * Camera_Component->getWorldToViewMatrix()) * glm::vec4(cursorDelta.x / Renderer::getInstance()->ScreenWidth * glm::dot((Z_Arrow->getComponent<Transform>()->getPosition() - Renderer::getMainCamera()->getComponent<Transform>()->getPosition()), cam_viewDir) * 2, 0,0,0);
			if (Trans_Delta_WS.z > 0)
				Renderer::getInstance()->CurObjectTranslate_Z(glm::abs(Trans_Delta_WS.x * X_Weight) + Trans_Delta_WS.z * Z_Weight);
			else if (Trans_Delta_WS.z < 0)
				Renderer::getInstance()->CurObjectTranslate_Z(-glm::abs(Trans_Delta_WS.x * X_Weight) + Trans_Delta_WS.z * Z_Weight);
			else
			{
				if (cam_viewDir.z > 0)
					Renderer::getInstance()->CurObjectTranslate_Z(Trans_Delta_WS.x * X_Weight);
				else
					Renderer::getInstance()->CurObjectTranslate_Z(-Trans_Delta_WS.x * X_Weight);
			}
		}
		break;
	}
	case ROTATION:
	{

		break;
	}
	case SCALE:
	{

		break;
	}
	default:
		break;
	}
}

Object * VisualTransformManager::getObjectById(GLint id)
{
	switch (mode)
	{
	case NONE:
		return nullptr;
	case TRANSLATION:
	{
		switch (id)
		{
		case 1:
			return X_Arrow;
		case 2:
			return Y_Arrow;
		case 3:
			return Z_Arrow;
		default:
			return nullptr;
			break;
		}
		break;
	}
	case ROTATION:
	{

		break;
	}
	case SCALE:
	{

		break;
	}
	default:
		break;
	}
	return nullptr;
}

void VisualTransformManager::RenderMeshes(Mesh * x_msh, Mesh * y_msh, Mesh * z_msh, glm::vec3 Pos)
{
	glUseProgram(pass->getProgramID());
	Camera* Cam_Component = Renderer::getMainCamera()->getComponent<Camera>();
	if (!Cam_Component)
		return;
	glm::mat4 CameraMatrix = Cam_Component->getWorldToViewMatrix();

	glm::mat4 projectionMatrix = Cam_Component->getProjectionMatrix();

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), Pos);
	glm::mat4 Zihao_MVP = projectionMatrix * CameraMatrix *  TransformMatrix;

	GLint uniformLocation = glGetUniformLocation(pass->getProgramID(), "Zihao_MVP");
	if (uniformLocation >= 0)
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &Zihao_MVP[0][0]);

	uniformLocation = glGetUniformLocation(pass->getProgramID(), "Alpha");
	if (uniformLocation >= 0)
		glUniform1f(uniformLocation, 0.65f);

	glBindVertexArray(x_msh->getVArrayID());
	uniformLocation = glGetUniformLocation(pass->getProgramID(), "PureColor");
	glUniform3fv(uniformLocation, 1, &glm::vec3(1.0, 0.0, 0.0)[0]);
	glDrawArrays(GL_TRIANGLES, 0, x_msh->getGeometry()->NF() * 3);

	glBindVertexArray(y_msh->getVArrayID());
	uniformLocation = glGetUniformLocation(pass->getProgramID(), "PureColor");
	glUniform3fv(uniformLocation, 1, &glm::vec3(0.0, 1.0, 0.0)[0]);
	glDrawArrays(GL_TRIANGLES, 0, x_msh->getGeometry()->NF() * 3);

	glBindVertexArray(z_msh->getVArrayID());
	uniformLocation = glGetUniformLocation(pass->getProgramID(), "PureColor");
	glUniform3fv(uniformLocation, 1, &glm::vec3(0.0, 0.0, 1.0)[0]);
	glDrawArrays(GL_TRIANGLES, 0, x_msh->getGeometry()->NF() * 3);

	Update_ObjTransform(Pos);
}

void VisualTransformManager::Update_ObjTransform(glm::vec3 Pos)
{
	X_Arrow->getComponent<Transform>()->setPosition(Pos);
	Y_Arrow->getComponent<Transform>()->setPosition(Pos);
	Z_Arrow->getComponent<Transform>()->setPosition(Pos);
}
