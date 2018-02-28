#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <Renderer.h>
#include <QtOpenGL\qglwidget>
#include <Qt\qapplication.h>



class MeGlWindow : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();
	void TimerInit();
	Renderer* renderer();

	QTimer* Timer;
	char* importFileName = nullptr;

	glm::vec2 clickPos;
	bool MouseHolder = false;
	bool StartTransform = false;

	Object* PrefetchObject;

	

public:
	void keyPressEvent(QKeyEvent*);
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void tryImportFile(char* filename);

private slots :
	void updateGL();
};

#endif
