#include <MeGlWindow.h>

Renderer* MeGlWindow::Zihao_renderer = nullptr;


void MeGlWindow::initializeGL()
{
	glewInit();
	TimerInit();
	resize(960, 720);
	renderer()->init(width(),height(),importFileName);
	


}

void MeGlWindow::paintGL()
{	
	renderer()->start();
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
	if (Zihao_renderer)
		return Zihao_renderer;
	else
	{
		Zihao_renderer = new Renderer();
		return Zihao_renderer;
	}
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
			renderer()->getCurrentCamera()->getComponent<Camera>()->move_forward();
			break;
		case Qt::Key::Key_S:
			renderer()->getCurrentCamera()->getComponent<Camera>()->move_backward();
			break;
		case Qt::Key::Key_A:
			renderer()->getCurrentCamera()->getComponent<Camera>()->move_leftward();
			break;
		case Qt::Key::Key_D:
			renderer()->getCurrentCamera()->getComponent<Camera>()->move_rightward();
			break;
		case Qt::Key::Key_R:
			renderer()->getCurrentCamera()->getComponent<Camera>()->move_upward();
			break;
		case Qt::Key::Key_F:
			renderer()->getCurrentCamera()->getComponent<Camera>()->move_downward();
			break;
		case Qt::Key::Key_Q:
			renderer()->getCurrentCamera()->getComponent<Camera>()->rotate_left();
			break;
		case Qt::Key::Key_E:
			renderer()->getCurrentCamera()->getComponent<Camera>()->rotate_right();
			break;
		case Qt::Key::Key_Z:
			renderer()->getCurrentCamera()->getComponent<Camera>()->rotate_up();
			break;
		case Qt::Key::Key_C:
			renderer()->getCurrentCamera()->getComponent<Camera>()->rotate_down();
			break;
		case Qt::Key::Key_F6:
			renderer()->ReCompileALLShader();
			break;
		case Qt::Key::Key_P:
			renderer()->getCurrentCamera()->getComponent<Camera>()->ChangePJ_Mode();
			break;
		case Qt::Key::Key_Tab:
			renderer()->SwitchToNextLight();
			break;
		case Qt::Key::Key_T:
		{
			Object* Cur_obj = renderer()->getCurrentObject();
			Cur_obj->ComputeCurrentBoundBox();
			renderer()->getCurrentCamera()->getComponent<Camera>()->CenterOnBoundingBox(Cur_obj->getCurrentBoundBoxMin(), Cur_obj->getCurrentBoundBoxMax());
			break;
		}
		default:
			break;
		}
	}
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
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
			renderer()->getCurrentCamera()->getComponent<Camera>()->mouse_RotateUpdate(glm::vec2(e->x(), e->y()));
			repaint();
		}
		else if (e->buttons() == Qt::RightButton)
		{
			renderer()->getCurrentCamera()->getComponent<Camera>()->mouse_TranslateUpdate(glm::vec2(e->x(), e->y()));
			repaint();
		}
	}
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
