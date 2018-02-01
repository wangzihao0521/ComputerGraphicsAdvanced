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
	switch (e->key())
	{
	case Qt::Key::Key_Escape:
		qApp->quit();
	case Qt::Key::Key_W:
		renderer()->getCurrentCamera()->move_forward();
		break;
	case Qt::Key::Key_S:
		renderer()->getCurrentCamera()->move_backward();
		break;
	case Qt::Key::Key_A:
		renderer()->getCurrentCamera()->move_leftward();
		break;
	case Qt::Key::Key_D:
		renderer()->getCurrentCamera()->move_rightward();
		break;
	case Qt::Key::Key_R:
		renderer()->getCurrentCamera()->move_upward();
		break;
	case Qt::Key::Key_F:
		renderer()->getCurrentCamera()->move_downward();
		break;
	case Qt::Key::Key_Q:
		renderer()->getCurrentCamera()->rotate_left();
		break;
	case Qt::Key::Key_E:
		renderer()->getCurrentCamera()->rotate_right();
		break;
	case Qt::Key::Key_Z:
		renderer()->getCurrentCamera()->rotate_up();
		break;
	case Qt::Key::Key_C:
		renderer()->getCurrentCamera()->rotate_down();
		break;
	case Qt::Key::Key_F6:
		renderer()->ReCompileALLShader();
		break;
	case Qt::Key::Key_P:
		renderer()->getCurrentCamera()->ChangePJ_Mode();
		break;
	case Qt::Key::Key_T:
	{
		Object* Cur_obj = renderer()->getCurrentObject();
		Cur_obj->ComputeCurrentBoundBox();
		renderer()->getCurrentCamera()->CenterOnBoundingBox(Cur_obj->getCurrentBoundBoxMin(), Cur_obj->getCurrentBoundBoxMax());
		break;
	}
	default:
		break;
	}
}

void MeGlWindow::mouseMoveEvent(QMouseEvent* e)
{
	if (e->buttons() == Qt::LeftButton)
	{
		renderer()->getCurrentCamera()->mouse_RotateUpdate(glm::vec2(e->x(), e->y()));
		repaint();
	}
	else if (e->buttons() == Qt::RightButton)
	{
		renderer()->getCurrentCamera()->mouse_TranslateUpdate(glm::vec2(e->x(), e->y()));
		repaint();
	}
}

void MeGlWindow::tryImportFile(char * filename)
{
	importFileName = filename;
}

void MeGlWindow::updateGL()
{
	repaint();
}
