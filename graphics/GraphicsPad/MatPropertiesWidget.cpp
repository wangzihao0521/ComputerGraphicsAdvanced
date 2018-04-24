#include "MatPropertiesWidget.h"
#include "Material.h"

MatPropertiesWidget::MatPropertiesWidget(Material* mat, QWidget* parent) : QWidget(parent),material(mat)
{
	MainLayout = new QVBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	MainLayout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(MainLayout);
	FileTypeLabel = new QLabel(tr("Material File"));
	MainLayout->addWidget(FileTypeLabel);
	NameLayout = new QHBoxLayout;
	NameLayout->setAlignment(Qt::AlignLeft);
	MainLayout->addLayout(NameLayout);
	NameLabel = new QLabel(tr("Name"));
	matName = new QLabel;
	matName->setText(QString::fromStdString(mat->getName()));

	NameLayout->addWidget(NameLabel);
	NameLayout->addWidget(matName);

	_CreateVertexShader();
	_CreateFragmentShader();

	_CreateAmbientColor();
	_CreateDiffuseColor();
	_CreateSpecularColor();
	_CreateSpecularExp();
	_CreateAmbientTexture();
	_CreateDiffuseTexture();
	_CreateSpecularTexture();
	
}

MatPropertiesWidget::~MatPropertiesWidget()
{
	delete MainLayout;
	MainLayout = nullptr;
	delete FileTypeLabel;
	FileTypeLabel = nullptr;
	delete NameLabel;
	NameLabel = nullptr;
	delete matName;
	matName = nullptr;

	delete KaLabel;
	KaLabel = nullptr;
	delete Ka0;
	Ka0 = nullptr;
	delete Ka1;
	Ka1 = nullptr;
	delete Ka2;
	Ka2 = nullptr;

	delete KdLabel;
	KdLabel = nullptr;
	delete Kd0;
	Kd0 = nullptr;
	delete Kd1;
	Kd1 = nullptr;
	delete Kd2;
	Kd2 = nullptr;

	delete KsLabel;
	KsLabel = nullptr;
	delete Ks0;
	Ks0 = nullptr;
	delete Ks1;
	Ks1 = nullptr;
	delete Ks2;
	Ks2 = nullptr;

	delete NsLabel;
	NsLabel = nullptr;
	delete Ns;
	Ns = nullptr;

	delete Ka_mapLabel;
	Ka_mapLabel = nullptr;
	delete Ka_map;
	Ka_map = nullptr;

	delete Kd_mapLabel;
	Kd_mapLabel = nullptr;
	delete Kd_map;
	Kd_map = nullptr;

	delete Ks_mapLabel;
	Ks_mapLabel = nullptr;
	delete Ks_map;
	Ks_map = nullptr;
	material = nullptr;
}

void MatPropertiesWidget::_CreateVertexShader()
{
	VShaderLayout = new QHBoxLayout;
	VShaderLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(VShaderLayout);
	VShaderLabel = new QLabel(tr("Vertex Shader:"));
	VertexShader = new QLineEdit;
	VertexShader->setText(QString::fromLatin1(material->PassArray[0]->getVshaderFileName()));
	VertexShader->setMaximumHeight(25);
	VShaderLayout->addWidget(VShaderLabel);
	VShaderLayout->addWidget(VertexShader);
	connect(VertexShader, SIGNAL(editingFinished()), this, SLOT(_ShaderChanged()));
}

void MatPropertiesWidget::_CreateFragmentShader()
{
	FShaderLayout = new QHBoxLayout;
	FShaderLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(FShaderLayout);
	FShaderLabel = new QLabel(tr("Vertex Shader:"));
	FragmentShader = new QLineEdit;
	FragmentShader->setText(QString::fromLatin1(material->PassArray[0]->getFshaderFileName()));
	FragmentShader->setMaximumHeight(25);
	FShaderLayout->addWidget(FShaderLabel);
	FShaderLayout->addWidget(FragmentShader);
	connect(FragmentShader, SIGNAL(editingFinished()), this, SLOT(_ShaderChanged()));
}

void MatPropertiesWidget::_CreateAmbientColor()
{
	KaLayout = new QHBoxLayout;
	KaLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(KaLayout);
	KaLabel = new QLabel(tr("Ambient Color:"));
	Ka0 = new QLineEdit;
	Ka1 = new QLineEdit;
	Ka2 = new QLineEdit;
	Ka0->setText(QString::number(material->Ka[0]));
	Ka1->setText(QString::number(material->Ka[1]));
	Ka2->setText(QString::number(material->Ka[2]));
	Ka0->setMaximumHeight(25);
	Ka1->setMaximumHeight(25);
	Ka2->setMaximumHeight(25);
	KaLayout->addWidget(KaLabel);
	KaLayout->addWidget(Ka0);
	KaLayout->addWidget(Ka1);
	KaLayout->addWidget(Ka2);
	connect(Ka0, SIGNAL(editingFinished()), this, SLOT(_KaChanged()));
	connect(Ka1, SIGNAL(editingFinished()), this, SLOT(_KaChanged()));
	connect(Ka2, SIGNAL(editingFinished()), this, SLOT(_KaChanged()));
}

void MatPropertiesWidget::_CreateDiffuseColor()
{
	KdLayout = new QHBoxLayout;
	KdLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(KdLayout);
	KdLabel = new QLabel(tr("Diffuse  Color:"));
	Kd0 = new QLineEdit;
	Kd1 = new QLineEdit;
	Kd2 = new QLineEdit;
	Kd0->setText(QString::number(material->Kd[0]));
	Kd1->setText(QString::number(material->Kd[1]));
	Kd2->setText(QString::number(material->Kd[2]));
	Kd0->setMaximumHeight(25);
	Kd1->setMaximumHeight(25);
	Kd2->setMaximumHeight(25);
	KdLayout->addWidget(KdLabel);
	KdLayout->addWidget(Kd0);
	KdLayout->addWidget(Kd1);
	KdLayout->addWidget(Kd2);
	connect(Kd0, SIGNAL(editingFinished()), this, SLOT(_KdChanged()));
	connect(Kd1, SIGNAL(editingFinished()), this, SLOT(_KdChanged()));
	connect(Kd2, SIGNAL(editingFinished()), this, SLOT(_KdChanged()));
}

void MatPropertiesWidget::_CreateSpecularColor()
{
	KsLayout = new QHBoxLayout;
	KsLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(KsLayout);
	KsLabel = new QLabel(tr("Specualr Color:"));
	Ks0 = new QLineEdit;
	Ks1 = new QLineEdit;
	Ks2 = new QLineEdit;
	Ks0->setText(QString::number(material->Ks[0]));
	Ks1->setText(QString::number(material->Ks[1]));
	Ks2->setText(QString::number(material->Ks[2]));
	Ks0->setMaximumHeight(25);
	Ks1->setMaximumHeight(25);
	Ks2->setMaximumHeight(25);
	KsLayout->addWidget(KsLabel);
	KsLayout->addWidget(Ks0);
	KsLayout->addWidget(Ks1);
	KsLayout->addWidget(Ks2);
	connect(Ks0, SIGNAL(editingFinished()), this, SLOT(_KsChanged()));
	connect(Ks1, SIGNAL(editingFinished()), this, SLOT(_KsChanged()));
	connect(Ks2, SIGNAL(editingFinished()), this, SLOT(_KsChanged()));
}

void MatPropertiesWidget::_CreateSpecularExp()
{
	NsLayout = new QHBoxLayout;
	NsLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(NsLayout);
	NsLabel = new QLabel(tr("Specular Exponent:"));
	Ns = new QLineEdit;
	Ns->setText(QString::number(material->Ns));
	Ns->setMaximumHeight(25);
	NsLayout->addWidget(NsLabel);
	NsLayout->addWidget(Ns);
	connect(Ns, SIGNAL(editingFinished()), this, SLOT(_NsChanged()));
}

void MatPropertiesWidget::_CreateAmbientTexture()
{
	Ka_mapLayout = new QHBoxLayout;
	Ka_mapLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(Ka_mapLayout);
	Ka_mapLabel = new QLabel(tr("Ambient Map:"));
	QIcon texIcon(QString::fromStdString(material->map_Ka ? material->map_Ka ->getFileName() : "Assets\\blank.png"));
	QPixmap pixmap = texIcon.pixmap(QSize(60, 60), QIcon::Normal, QIcon::On);
	Ka_map = new QLabel;
	Ka_map->setPixmap(pixmap);
	Ka_map->setEnabled(!pixmap.isNull());

	Ka_mapLayout->addWidget(Ka_mapLabel);
	Ka_mapLayout->addWidget(Ka_map);

}

void MatPropertiesWidget::_CreateDiffuseTexture()
{
	Kd_mapLayout = new QHBoxLayout;
	Kd_mapLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(Kd_mapLayout);
	Kd_mapLabel = new QLabel(tr("Diffuse Map:"));
	QIcon texIcon(QString::fromStdString(material->map_Kd ? material->map_Kd->getFileName() : "Assets\\blank.png"));
	QPixmap pixmap = texIcon.pixmap(QSize(60, 60), QIcon::Normal, QIcon::On);
	Kd_map = new QLabel;
	Kd_map->setPixmap(pixmap);
	Kd_map->setEnabled(!pixmap.isNull());

	Kd_mapLayout->addWidget(Kd_mapLabel);
	Kd_mapLayout->addWidget(Kd_map);
}

void MatPropertiesWidget::_CreateSpecularTexture()
{
	Ks_mapLayout = new QHBoxLayout;
	Ks_mapLayout->setAlignment(Qt::AlignTop);
	MainLayout->addLayout(Ks_mapLayout);
	Ks_mapLabel = new QLabel(tr("Specualr Map:"));
	QIcon texIcon(QString::fromStdString(material->map_Ks ? material->map_Ks->getFileName() : "Assets\\blank.png"));
	QPixmap pixmap = texIcon.pixmap(QSize(60, 60), QIcon::Normal, QIcon::On);
	Ks_map = new QLabel;
	Ks_map->setPixmap(pixmap);
	Ks_map->setEnabled(!pixmap.isNull());

	Ks_mapLayout->addWidget(Ks_mapLabel);
	Ks_mapLayout->addWidget(Ks_map);
}

void MatPropertiesWidget::_KaChanged()
{
	bool ok;
	float newka0 = Ka0->text().toFloat(&ok);
	float newka1 = Ka1->text().toFloat(&ok);
	float newka2 = Ka2->text().toFloat(&ok);

	material->set_Ka(newka0, newka1, newka2);
}

void MatPropertiesWidget::_KdChanged()
{
	bool ok;
	float newkd0 = Kd0->text().toFloat(&ok);
	float newkd1 = Kd1->text().toFloat(&ok);
	float newkd2 = Kd2->text().toFloat(&ok);

	material->set_Kd(newkd0, newkd1, newkd2);
}

void MatPropertiesWidget::_KsChanged()
{
	bool ok;
	float newks0 = Ks0->text().toFloat(&ok);
	float newks1 = Ks1->text().toFloat(&ok);
	float newks2 = Ks2->text().toFloat(&ok);

	material->set_Ks(newks0, newks1, newks2);
}

void MatPropertiesWidget::_NsChanged()
{
	bool ok;
	float newNs = Ns->text().toFloat(&ok);

	material->set_Ns(newNs);
}

void MatPropertiesWidget::_mapKaChanged()
{
}

void MatPropertiesWidget::_mapKdChanged()
{
}

void MatPropertiesWidget::_mapKsChanged()
{
}

void MatPropertiesWidget::_ShaderChanged()
{
	material->PassArray[0]->setVshaderFileName(VertexShader->text().toLatin1().data());
	material->PassArray[0]->setFshaderFileName(FragmentShader->text().toLatin1().data());
	material->ReCompileShaders();
}
