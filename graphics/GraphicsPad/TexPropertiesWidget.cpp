#include "TexPropertiesWidget.h"
#include "Texture.h"

TexPropertiesWidget::TexPropertiesWidget(Texture* tex, QWidget* parent) : QWidget(parent), texture(tex)
{
	MainLayout = new QVBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	MainLayout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(MainLayout);
	FileTypeLabel = new QLabel(tr("Texture File"));
	MainLayout->addWidget(FileTypeLabel);
	NameLayout = new QHBoxLayout;
	NameLayout->setAlignment(Qt::AlignLeft);
	MainLayout->addLayout(NameLayout);
	NameLabel = new QLabel(tr("Path:"));
	texName = new QLabel;
	texName->setText(QString::fromStdString(tex->getFileName()));

	NameLayout->addWidget(NameLabel);
	NameLayout->addWidget(texName);
}

TexPropertiesWidget::~TexPropertiesWidget()
{
	texture = nullptr;

	delete MainLayout;
	MainLayout = nullptr;
	delete FileTypeLabel;
	FileTypeLabel = nullptr;
	delete NameLabel;
	NameLabel = nullptr;
	delete texName;
	texName = nullptr;
}
