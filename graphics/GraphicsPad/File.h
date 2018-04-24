#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qicon.h>
#include <QtGui\qlabel.h>

class File : public QWidget
{
public:
	File(QIcon& Icon, std::string fname);
	virtual ~File();

	void _Select();
	void _UnSelect();

	virtual void _DisplayProperties() = 0;

protected:
	QIcon icon;
	std::string filename;
	QLabel* IconLabel;
	QLabel* NameLabel;

	void enterEvent(QEvent* e);
	void leaveEvent(QEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);

	virtual void _PutInScene(QMouseEvent* e) = 0;
	virtual void _PutInObjProperties(QMouseEvent* e) = 0;

private:
	bool MouseHolder;
	QPoint clickPos;
	
	
};
