#include <MeGlWindow.h>
#include "VisualTransformManager.h"

void MeGlWindow::initializeGL()
{
	glewInit();
	TimerInit();
	resize(960, 720);
	renderer()->init(width(),height(),importFileName);

	PrefetchObject = nullptr;
}

void MeGlWindow::paintGL()
{	
	renderer()->Start();
}

void MeGlWindow::TimerInit()
{
	Timer = new QTimer();
	Timer->setInterval(0);
	Timer->start();
	connect(Timer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

Renderer* MeGlWindow::renderer()
{
	return Renderer::getInstance();
}

void MeGlWindow::keyPressEvent(QKeyEvent * e)
{
	if (e->modifiers() && Qt::ControlModifier)
	{
		switch (e->key())
		{
		case Qt::Key::Key_R:
		{
			std::vector<Object*> cur_obj = renderer()->getCurrentObject();
			for (auto iter = cur_obj.begin(); iter != cur_obj.end(); ++iter)
			{
				Mesh_Renderer* mr_component = (*iter)->getComponent<Mesh_Renderer>();
				if (mr_component)
					mr_component->ReceiveShadow_Change();
			}
			break;
		}
		case Qt::Key::Key_C:
		{
			std::vector<Object*> cur_obj = renderer()->getCurrentObject();
			for (auto iter = cur_obj.begin(); iter != cur_obj.end(); ++iter)
			{
				Mesh_Renderer* mr_component = (*iter)->getComponent<Mesh_Renderer>();
				if (mr_component)
					mr_component->CastShadow_Change();
			}
			break;
		}
		case Qt::Key::Key_H:
		{
			std::vector<Object*> cur_obj = renderer()->getCurrentObject();
			for (auto iter = cur_obj.begin(); iter != cur_obj.end(); ++iter)
			{
				(*iter)->Hide_Change();
			}
			break;
		}
		case Qt::Key::Key_S:
		{
			std::vector<Object*> cur_obj = renderer()->getCurrentObject();
			for (auto iter = cur_obj.begin(); iter != cur_obj.end(); ++iter)
			{
				Light* light_component = (*iter)->getComponent<Light>();
				if (light_component)
					light_component->getShadowInfo()->Cast_Shadow_Change();
			}
			break;
		}
		case Qt::Key::Key_T:
		{
			std::vector<Object*> cur_obj = renderer()->getCurrentObject();
			for (auto iter = cur_obj.begin(); iter != cur_obj.end(); ++iter)
			{
				Light* light_component = (*iter)->getComponent<Light>();
				if (light_component)
					light_component->changeType();
			}
			break;
		}
		case Qt::Key::Key_I:
		{
			std::vector<Object*> cur_obj = renderer()->getCurrentObject();
			for (auto iter = cur_obj.begin(); iter != cur_obj.end(); ++iter)
			{
				Light* light_component = (*iter)->getComponent<Light>();
				if (light_component)
					light_component->AddIntensity(0.1);
			}
			break;
		}
		case Qt::Key::Key_J:
		{
			std::vector<Object*> cur_obj = renderer()->getCurrentObject();
			for (auto iter = cur_obj.begin(); iter != cur_obj.end(); ++iter)
			{
				Light* light_component = (*iter)->getComponent<Light>();
				if (light_component)
					light_component->AddIntensity(-0.1);
			}
			break;
		}
		default:
			break;
		}
	}
	else
	{
		switch (e->key())
		{
		case Qt::Key::Key_Escape:
			qApp->quit();
		case Qt::Key::Key_Delete:
			renderer()->deleteCurrentObjects();
		case Qt::Key::Key_W:
			renderer()->getMainCamera()->getComponent<Camera>()->move_forward();
			break;
		case Qt::Key::Key_S:
			renderer()->getMainCamera()->getComponent<Camera>()->move_backward();
			break;
		case Qt::Key::Key_A:
			renderer()->getMainCamera()->getComponent<Camera>()->move_leftward();
			break;
		case Qt::Key::Key_D:
			renderer()->getMainCamera()->getComponent<Camera>()->move_rightward();
			break;
		case Qt::Key::Key_R:
			renderer()->getMainCamera()->getComponent<Camera>()->move_upward();
			break;
		case Qt::Key::Key_F:
			renderer()->getMainCamera()->getComponent<Camera>()->move_downward();
			break;
		case Qt::Key::Key_Q:
			renderer()->getMainCamera()->getComponent<Camera>()->rotate_left();
			break;
		case Qt::Key::Key_E:
			renderer()->getMainCamera()->getComponent<Camera>()->rotate_right();
			break;
		case Qt::Key::Key_Z:
			renderer()->getMainCamera()->getComponent<Camera>()->rotate_up();
			break;
		case Qt::Key::Key_C:
			renderer()->getMainCamera()->getComponent<Camera>()->rotate_down();
			break;
		case Qt::Key::Key_F6:
			renderer()->ReCompileALLShader();
			break;
		case Qt::Key::Key_P:
		{
			renderer()->getMainCamera()->getComponent<Camera>()->ChangePJ_Mode();
			break;
		}
		case Qt::Key::Key_Tab:
			renderer()->SwitchToNextLight();
			break;
		/*case Qt::Key::Key_T:
		{
			std::vector<Object*> Cur_obj = renderer()->getCurrentObject();
			for (auto iter = Cur_obj.begin(); iter != Cur_obj.end(); ++iter)
			{
				(*iter)->ComputeCurrentBoundBox();
				renderer()->getMainCamera()->getComponent<Camera>()->CenterOnBoundingBox((*iter)->getCurrentBoundBoxMin(), (*iter)->getCurrentBoundBoxMax());
			}
			break;
		}*/
		case Qt::Key::Key_L:
		{
			Object* light = renderer()->CreateLightInScene();
			break;
		}
		default:
			break;
		}
	}
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	glm::vec2 mouseDelta = glm::vec2(e->x(), e->y()) - oldMousePosition;
	oldMousePosition = glm::vec2(e->x(), e->y());
	if (StartTransform)
	{
		setMouseTracking(true);
		VisualTransformManager::getInstance()->executeTransform(PrefetchObject, mouseDelta);
	}
	else
	{
		if (e->modifiers() && Qt::ControlModifier)
		{
			if (e->buttons() == Qt::LeftButton)
			{
				renderer()->getCurrentLight()->getComponent<Light>()->mouse_RotateUpdate(glm::vec2(e->x(), e->y()));
				repaint();
			}
		}
		else
		{
			if (e->buttons() == Qt::LeftButton)
			{
				renderer()->getMainCamera()->getComponent<Camera>()->mouse_RotateUpdate(glm::vec2(e->x(), e->y()));
				repaint();
			}
			else if (e->buttons() == Qt::RightButton)
			{
				renderer()->getMainCamera()->getComponent<Camera>()->mouse_TranslateUpdate(glm::vec2(e->x(), e->y()));
				repaint();
			}
		}
	}
}

void MeGlWindow::mousePressEvent(QMouseEvent * e)
{
	if (!MouseHolder)
	{
		if (e->button() == Qt::LeftButton)
		{
			clickPos = glm::vec2(e->x(), e->y());
			oldMousePosition = clickPos;
			PrefetchObject = Renderer::getInstance()->getObjectByScreenPos(clickPos);
			if (PrefetchObject && PrefetchObject->IsTransformationObject())
			{
				StartTransform = true;
			}
		}
		MouseHolder = true;
	}
}

void MeGlWindow::mouseReleaseEvent(QMouseEvent * e)
{
	if (e->button() == Qt::LeftButton)
	{
		if (!PrefetchObject)
			Renderer::getInstance()->ClearCurrentObject();
		else if (PrefetchObject->IsNormalObject())
		{
			glm::vec2 mouseDelta = glm::vec2(e->x(), e->y()) - clickPos;
			if (glm::length(mouseDelta) < 20.0f)
			{
				if (e->modifiers() && Qt::ControlModifier)
					Renderer::getInstance()->AddCurrentObject(PrefetchObject);
				else
				{
					Renderer::getInstance()->ClearCurrentObject();
					Renderer::getInstance()->AddCurrentObject(PrefetchObject);
				}
			}
		}		
		clickPos = glm::vec2(0, 0);
	}
	MouseHolder = false;
	StartTransform = false;
	setMouseTracking(false);
}

void MeGlWindow::tryImportFile(char * filename)
{
	importFileName = filename;
}

void MeGlWindow::updateGL()
{
//	renderer()->getCurrentObject()->getComponent<Transform>()->rotate(glm::vec3(0.0, 0.0, 0.05));
	repaint();
}
