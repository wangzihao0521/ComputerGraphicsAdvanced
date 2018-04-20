#include "SceneObjManager.h"
#include "ObjectLabel.h"
#include "Renderer.h"

SceneObjManager* SceneObjManager::InstancePtr = nullptr;

SceneObjManager::SceneObjManager()
{
	setMinimumSize(160, 180);
	resize(320, 360);

	//	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	MainLayout = new QVBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	setLayout(MainLayout);
	setStyleSheet("background-color:white;");

	InstancePtr = this;
}

SceneObjManager::~SceneObjManager()
{
}

void SceneObjManager::AddLabel(ObjectLabel* ObjLabel)
{
	MainLayout->addWidget(ObjLabel);
	AllLabels.push_back(ObjLabel);
}

SceneObjManager * SceneObjManager::getInstance()
{
	if (InstancePtr)
		return InstancePtr;
	else
	{
		InstancePtr = new SceneObjManager;
		return InstancePtr;
	}
	return nullptr;
}

void SceneObjManager::_UnSelectAll()
{
	Renderer::getInstance()->ClearCurrentObject();
}

void SceneObjManager::mousePressEvent(QMouseEvent * e)
{
	_UnSelectAll();
}
