#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qicon.h>
#include <QtGui\qlabel.h>

class ObjectLabel;

class SceneObjManager : public QWidget
{
public:
	SceneObjManager();
	~SceneObjManager();

	void AddLabel(ObjectLabel* ObjLabel);
	void _UnSelectAll();

	static SceneObjManager * getInstance();

private:
	static SceneObjManager * InstancePtr;
	QVBoxLayout* MainLayout;

protected:
	std::list<ObjectLabel*> AllLabels;

	void mousePressEvent(QMouseEvent * e);
};
