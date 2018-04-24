#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qicon.h>
#include <QtGui\qlabel.h>
#include <QtGui\qlineedit.h>

class Texture;

class TexPropertiesWidget : public QWidget
{
public :
	TexPropertiesWidget(Texture* tex, QWidget* parent = 0);
	~TexPropertiesWidget();

protected:
	Texture* texture;

private:
	QVBoxLayout* MainLayout;
	QLabel* FileTypeLabel;
	QHBoxLayout* NameLayout;
	QLabel* NameLabel;
	QLabel* texName;
};
