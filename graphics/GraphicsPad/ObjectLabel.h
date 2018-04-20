#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qicon.h>
#include <QtGui\qlabel.h>

class Object;

class ObjectLabel : public QWidget
{
public: 
	ObjectLabel(Object* obj);
	~ObjectLabel();

	void _UnSelect();
	void _Select();
	void SetSelected(bool b);

protected:
	Object* object;
	QLabel* label;

	void mousePressEvent(QMouseEvent * e);

};
