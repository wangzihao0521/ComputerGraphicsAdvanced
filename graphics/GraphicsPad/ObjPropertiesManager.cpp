#include "ObjPropertiesManager.h"
#include "File.h"
#include "Texture.h"
#include "Material.h"

ObjPropertiesManager* ObjPropertiesManager::InstancePtr = nullptr;

ObjPropertiesManager::ObjPropertiesManager() : meshProperties(nullptr),matProperties(nullptr),texProperties(nullptr)
{
	setMinimumSize(640, 540);
	resize(1280, 1080);

	//	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	MainLayout = new QVBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	setLayout(MainLayout);
	setStyleSheet("background-color:white;");

	InstancePtr = this;
}

ObjPropertiesManager::~ObjPropertiesManager()
{
}

ObjPropertiesManager * ObjPropertiesManager::getInstance()
{
	if (InstancePtr)
		return InstancePtr;
	return nullptr;
}

void ObjPropertiesManager::Refresh(File * file)
{
	if (meshProperties)
	{
		delete meshProperties;
		meshProperties = nullptr;
	}
	if (matProperties)
	{
		delete matProperties;
		matProperties = nullptr;
	}
	if (texProperties)
	{
		delete texProperties;
		texProperties = nullptr;
	}
	file->_DisplayProperties();
}

void ObjPropertiesManager::Refresh(Object * obj)
{
}

void ObjPropertiesManager::Try_ChangeTex(QPoint & point, Texture * tex)
{
	if (!matProperties)
		return;
	QWidget* child = matProperties->childAt(point);
	if (!child)
		return;
	QLabel* label = dynamic_cast<QLabel*>(child);
	if (!label)
		return;
	if (!label->pixmap())
		return;

	QIcon texIcon(QString::fromStdString(tex->getFileName()));
	QPixmap pixmap = texIcon.pixmap(QSize(60, 60), QIcon::Normal, QIcon::On);
	label->setPixmap(pixmap);
	label->setEnabled(!pixmap.isNull());

	if (label == matProperties->Ka_map)
		matProperties->material->BindAmbientMap(tex);
	if (label == matProperties->Kd_map)
		matProperties->material->BindDiffuseMap(tex);
	if (label == matProperties->Ks_map)
		matProperties->material->BindSpecularMap(tex);
}

void ObjPropertiesManager::DisplayMesh(Mesh * mesh)
{
	meshProperties = new MeshPropertiesWidget(mesh, this);
	MainLayout->addWidget(meshProperties);
	meshProperties->show();
}

void ObjPropertiesManager::DisplayMaterial(Material * mat)
{
	matProperties = new MatPropertiesWidget(mat, this);
	MainLayout->addWidget(matProperties);
	matProperties->show();
}

void ObjPropertiesManager::DisplayTexture(Texture * tex)
{
	texProperties = new TexPropertiesWidget(tex, this);
	MainLayout->addWidget(texProperties);
	texProperties->show();
}
