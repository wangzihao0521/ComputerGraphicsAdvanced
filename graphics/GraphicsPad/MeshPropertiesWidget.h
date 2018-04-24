#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qlabel.h>

class Mesh;

class MeshPropertiesWidget : public QWidget
{
public:
	MeshPropertiesWidget(Mesh* mesh, QWidget* parent = 0);
	~MeshPropertiesWidget();

protected:
	Mesh* mesh;
private:
	QVBoxLayout* MainLayout;
	QLabel* FileTypeLabel;
	QHBoxLayout* NameLayout;
	QLabel* NameLabel;
	QLabel* MeshName;
	QHBoxLayout* NVLayout;
	QLabel* NVLabel;
	QLabel* NV;
	QHBoxLayout* NFLayout;
	QLabel* NFLabel;
	QLabel* NF;

};

