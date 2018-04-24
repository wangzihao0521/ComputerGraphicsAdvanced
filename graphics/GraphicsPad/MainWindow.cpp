#include "MainWindow.h"
#include <QtGui\qmenubar.h>
#include <Qt\qfiledialog.h>

MainWindow* MainWindow::InstancePtr = nullptr;

MainWindow::MainWindow()
{
	InstancePtr = this;

	//Window Settings
	setWindowTitle(tr("ZihaoRenderer"));
	setMinimumSize(960, 540);
	resize(1920, 1080);

	//menu on the top
	QWidget* EntireWidget = new QWidget;
	setCentralWidget(EntireWidget);

	QGridLayout * EntireWidgetlayout = new QGridLayout;
	EntireWidget->setLayout(EntireWidgetlayout);

	CreateActions();
	CreateMenus();
	
	//Scene
	CreateSceneGroupBox();

	//File
	CreateFileManagerGroupBox();

	//Scene Object Manager
	CreateSceneObjManagerGroupBox();

	//Object Properties
	CreateObjectPropertiesGroupBox();

	EntireWidgetlayout->addWidget(SceneGroupBox, 0, 1, 2, 3);
	EntireWidgetlayout->addWidget(FileManagerGroupBox, 2, 0, 1, 4);
	EntireWidgetlayout->addWidget(SceneObjManagerGroupBox, 0, 0, 2, 1);
	EntireWidgetlayout->addWidget(ObjectPropertiesGroupBox, 0, 4, 3, 2);
	int a = EntireWidgetlayout->columnCount();
	int b = EntireWidgetlayout->rowCount();

}

void MainWindow::import()
{
	std::string filename(QFileDialog::getOpenFileName(this, "Select a file to open...", QDir::homePath()).toLatin1().data());
	std::string fileType = filename.substr(filename.find(".")+1, filename.size() - filename.find("."));
	if (fileType == "obj")
	{
		Mesh* NewMesh = GLWindow->renderer()->ImportObj(QString::fromStdString(filename).toLatin1().data());
		if (NewMesh)
		{
			File_Window->AddFile(NewMesh);
		}
	}
}

MainWindow * MainWindow::getInstance()
{
	if (InstancePtr)
		return InstancePtr;
	return nullptr;
}

MeGlWindow * MainWindow::getScene()
{
	if (GLWindow)
		return GLWindow;
	return nullptr;
}

void MainWindow::CreatePointLight()
{
	Object* obj = GLWindow->renderer()->CreateLightInScene();
	obj->getComponent<Light>()->getShadowInfo()->Cast_Shadow_Change();
}

void MainWindow::CreateDirectionalLight()
{
	Object* obj = GLWindow->renderer()->CreateLightInScene();
	obj->getComponent<Light>()->getShadowInfo()->Cast_Shadow_Change();
	obj->getComponent<Light>()->changeType();
}

void MainWindow::CreateActions()
{
	ImportAct = new QAction(tr("&Import"), this);
	connect(ImportAct, SIGNAL(triggered()), this, SLOT(import()));

	PointLightAct = new QAction(tr("&PointLight"), this);
	connect(PointLightAct, SIGNAL(triggered()), this, SLOT(CreatePointLight()));

	DirectionalLightAct = new QAction(tr("&DirecitonalLight"), this);
	connect(DirectionalLightAct, SIGNAL(triggered()), this, SLOT(CreateDirectionalLight()));
}

void MainWindow::CreateMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(ImportAct);

	GameObjectMenu = menuBar()->addMenu(tr("&GameObject"));
	LightMenu = GameObjectMenu->addMenu(tr("&Light"));
	LightMenu->addAction(PointLightAct);
	LightMenu->addAction(DirectionalLightAct);
}

void MainWindow::CreateSceneGroupBox()
{
	SceneGroupBox = new QGroupBox(tr("Scene"));

	GLWindow = new MeGlWindow;
	GLWindow->setFocusPolicy(Qt::ClickFocus);
	GLWindow->show();
	QVBoxLayout* SceneLayout = new QVBoxLayout;
	SceneLayout->addWidget(GLWindow);
	SceneGroupBox->setLayout(SceneLayout);
}

void MainWindow::CreateFileManagerGroupBox()
{
	FileManagerGroupBox = new QGroupBox(tr("File"));
	File_Window = new FileWindow;
	File_Window->show();
	QHBoxLayout* FileWindowLayout = new QHBoxLayout;
	FileWindowLayout->addWidget(File_Window);
	FileManagerGroupBox->setLayout(FileWindowLayout);
}

void MainWindow::CreateSceneObjManagerGroupBox()
{
	SceneObjManagerGroupBox = new QGroupBox(tr("Scene Object Manager"));
	SceneObjManager_Window = new SceneObjManager;
	SceneObjManager_Window->show();
	QVBoxLayout* SceneObjManagerLayout = new QVBoxLayout;
	SceneObjManagerLayout->addWidget(SceneObjManager_Window);
	SceneObjManagerGroupBox->setLayout(SceneObjManagerLayout);

}

void MainWindow::CreateObjectPropertiesGroupBox()
{
	ObjectPropertiesGroupBox = new QGroupBox(tr("Object Properties"));
	ObjProperties_Window = new ObjPropertiesManager;
	ObjProperties_Window->show();
	QVBoxLayout* ObjectPropertiesLayout = new QVBoxLayout;
	ObjectPropertiesLayout->addWidget(ObjProperties_Window);
	ObjectPropertiesGroupBox->setLayout(ObjectPropertiesLayout);

}
