#include <MeGlWindow.h>

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
	renderer()->RenderToScene();
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
		case Qt::Key::Key_W:
			renderer()->getCurrentLight()->getComponent<Transform>()->translate(glm::vec3(0,0,-Object::Movement_speed));
			break;
		case Qt::Key::Key_S:
			renderer()->getCurrentLight()->getComponent<Transform>()->translate(glm::vec3(0, 0, Object::Movement_speed));
			break;
		case Qt::Key::Key_A:
			renderer()->getCurrentLight()->getComponent<Transform>()->translate(glm::vec3(-Object::Movement_speed, 0, 0));
			break;
		case Qt::Key::Key_D:
			renderer()->getCurrentLight()->getComponent<Transform>()->translate(glm::vec3(Object::Movement_speed, 0, 0));
			break;
		case Qt::Key::Key_R:
			renderer()->getCurrentLight()->getComponent<Transform>()->translate(glm::vec3(0, Object::Movement_speed, 0));
			break;
		case Qt::Key::Key_F:
			renderer()->getCurrentLight()->getComponent<Transform>()->translate(glm::vec3(0, -Object::Movement_speed, 0));
			break;
		case Qt::Key::Key_Q:
		{
			renderer()->getCurrentLight()->getComponent<Transform>()->rotate(glm::vec3(0, Object::Rotation_speed, 0));
			renderer()->getCurrentLight()->getComponent<Light>()->ReComputeLightDir();
			break;
		}
		case Qt::Key::Key_E:
		{
			renderer()->getCurrentLight()->getComponent<Transform>()->rotate(glm::vec3(0, -Object::Rotation_speed, 0));
			renderer()->getCurrentLight()->getComponent<Light>()->ReComputeLightDir();
			break;
		}
		case Qt::Key::Key_Z:
		{
			renderer()->getCurrentLight()->getComponent<Transform>()->rotate(glm::vec3(Object::Rotation_speed, 0, 0));
			renderer()->getCurrentLight()->getComponent<Light>()->ReComputeLightDir();
			break;
		}
		case Qt::Key::Key_C:
		{
			renderer()->getCurrentLight()->getComponent<Transform>()->rotate(glm::vec3(-Object::Rotation_speed, 0, 0));
			renderer()->getCurrentLight()->getComponent<Light>()->ReComputeLightDir();
			break;
		}
		case Qt::Key::Key_T:
			renderer()->getCurrentLight()->getComponent<Light>()->changeType();
			break;
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
			renderer()->getMainCamera()->getComponent<Camera>()->ChangePJ_Mode();
			break;
		case Qt::Key::Key_Tab:
			renderer()->SwitchToNextLight();
			break;
		case Qt::Key::Key_T:
		{
			std::vector<Object*> Cur_obj = renderer()->getCurrentObject();
			for (auto iter = Cur_obj.begin(); iter != Cur_obj.end(); ++iter)
			{
				(*iter)->ComputeCurrentBoundBox();
				renderer()->getMainCamera()->getComponent<Camera>()->CenterOnBoundingBox((*iter)->getCurrentBoundBoxMin(), (*iter)->getCurrentBoundBoxMax());
			}
			break;
		}
		default:
			break;
		}
	}
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	if (StartTransform)
	{

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
		if (PrefetchObject && PrefetchObject->IsNormalObject())
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
