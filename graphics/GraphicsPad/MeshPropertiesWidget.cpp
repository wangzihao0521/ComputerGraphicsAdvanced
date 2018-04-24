#include "MeshPropertiesWidget.h"
#include "Mesh.h"

MeshPropertiesWidget::MeshPropertiesWidget(Mesh * mesh,QWidget* parent) : QWidget(parent),mesh(mesh)
{
	MainLayout = new QVBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	setLayout(MainLayout);
	FileTypeLabel = new QLabel(tr("Mesh File"));
	MainLayout->addWidget(FileTypeLabel);
	NameLayout = new QHBoxLayout;
	NameLayout->setAlignment(Qt::AlignLeft);
	MainLayout->addLayout(NameLayout);
	NameLabel = new QLabel(tr("Name"));
	MeshName = new QLabel;
	MeshName->setText(QString::fromStdString(mesh->getName()));

	/*NameLabel ->setStyleSheet("background-color:red;color:black");
	MeshName->setStyleSheet("background-color:blue;color:black");*/
	NameLayout->addWidget(NameLabel);
	NameLayout->addWidget(MeshName);

	NVLayout = new QHBoxLayout;
	NVLayout->setAlignment(Qt::AlignLeft);
	MainLayout->addLayout(NVLayout);
	NVLabel = new QLabel(tr("Num of Vertices"));
	NV = new QLabel;
	NV->setText(QString::number(mesh->getGeometry()->NV()));

	/*NameLabel ->setStyleSheet("background-color:red;color:black");
	MeshName->setStyleSheet("background-color:blue;color:black");*/
	NVLayout->addWidget(NVLabel);
	NVLayout->addWidget(NV);

	NFLayout = new QHBoxLayout;
	NFLayout->setAlignment(Qt::AlignLeft);
	MainLayout->addLayout(NFLayout);
	NFLabel = new QLabel(tr("Num of Faces"));
	NF = new QLabel;
	NF->setText(QString::number(mesh->getGeometry()->NF()));

	/*NameLabel ->setStyleSheet("background-color:red;color:black");
	MeshName->setStyleSheet("background-color:blue;color:black");*/
	NFLayout->addWidget(NFLabel);
	NFLayout->addWidget(NF);

}

MeshPropertiesWidget::~MeshPropertiesWidget()
{
	delete MainLayout;
	MainLayout = nullptr;
	delete FileTypeLabel;
	FileTypeLabel = nullptr;
//	delete NameLayout;
	NameLayout = nullptr;
	delete NameLabel;
	NameLabel = nullptr;
	delete MeshName;
	MeshName = nullptr;
//	delete NVLayout;
	NVLayout = nullptr;
	delete NVLabel;
	NVLabel = nullptr;
	delete NV;
	NV = nullptr;
//	delete NFLayout;
	NFLayout = nullptr;
	delete NFLabel;
	NFLabel = nullptr;
	delete NF;
	NF = nullptr;
	mesh = nullptr;

}
