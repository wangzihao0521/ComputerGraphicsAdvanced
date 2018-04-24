#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qicon.h>
#include <QtGui\qlabel.h>
#include <QtGui\qlineedit.h>

class Object;

class ObjPropertiesWidget : public QWidget
{
public:
	ObjPropertiesWidget(Object* obj, QWidget* parent = 0);
	~ObjPropertiesWidget();

protected:
	Object* object;

private:
	QVBoxLayout* MainLayout;
	QLabel* FileTypeLabel;
	QHBoxLayout* NameLayout;
	QLabel* NameLabel;
	QLabel* objName;
};
