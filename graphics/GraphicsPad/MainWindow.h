#pragma once
#include "MeGlWindow.h"
#include "FileWindow.h"
#include "SceneObjManager.h"
#include <QtGui\qmainwindow.h>
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qgroupbox.h>


class MainWindow : public QMainWindow
{

	Q_OBJECT

public:
	MainWindow();
	
	static MainWindow* getInstance();
	MeGlWindow* getScene();

private slots:
	void import();
	void CreatePointLight();
	void CreateDirectionalLight();

private:

	static MainWindow* InstancePtr;

	QMenu* fileMenu;
	QMenu* GameObjectMenu;
	QMenu* LightMenu;
	QAction* ImportAct;
	QAction* PointLightAct;
	QAction* DirectionalLightAct;

	void CreateActions();
	void CreateMenus();

	QGroupBox* SceneGroupBox;
	QGroupBox* FileManagerGroupBox;
	QGroupBox* SceneObjManagerGroupBox;
	QGroupBox* ObjectPropertiesGroupBox;

	MeGlWindow* GLWindow;
	FileWindow* File_Window;
	SceneObjManager* SceneObjManager_Window;

	void CreateSceneGroupBox();
	void CreateFileManagerGroupBox();
	void CreateSceneObjManagerGroupBox();
	void CreateObjectPropertiesGroupBox();
};
