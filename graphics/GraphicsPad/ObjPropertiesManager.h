#pragma once
#include <QtGui\qwidget.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qicon.h>
#include <QtGui\qlabel.h>
#include "MeshPropertiesWidget.h"
#include "MatPropertiesWidget.h"
#include "TexPropertiesWidget.h"

class Object;
class File;
class Mesh;
class Material;
class Texture;

class  ObjPropertiesManager : public QWidget
{
public:
	ObjPropertiesManager();
	~ObjPropertiesManager();

	static ObjPropertiesManager* getInstance();

	void Refresh(File* file);
	void Refresh(Object* obj);
	void Try_ChangeTex(QPoint& point, Texture* tex);

	void DisplayMesh(Mesh* mesh);
	void DisplayMaterial(Material* mat);
	void DisplayTexture(Texture* tex);

protected:
	MeshPropertiesWidget* meshProperties;
	MatPropertiesWidget* matProperties;
	TexPropertiesWidget* texProperties;
	

private:
	static ObjPropertiesManager* InstancePtr;
	QVBoxLayout* MainLayout;
};
