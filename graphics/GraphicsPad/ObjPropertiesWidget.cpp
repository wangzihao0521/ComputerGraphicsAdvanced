#include "ObjPropertiesWidget.h"
#include "Object.h"

ObjPropertiesWidget::ObjPropertiesWidget(Object* obj, QWidget* parent) : QWidget(parent), object(obj)
{
	MainLayout = new QVBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	MainLayout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(MainLayout);
	NameLayout = new QHBoxLayout;
	NameLayout->setAlignment(Qt::AlignLeft);
	MainLayout->addLayout(NameLayout);
	NameLabel = new QLabel(tr("Name"));
	objName = new QLabel;
	objName->setText(QString::fromStdString(obj->getName()));

	NameLayout->addWidget(NameLabel);
	NameLayout->addWidget(objName);

	QFrame* line = new QFrame;
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	MainLayout->addWidget(line);
	
}

ObjPropertiesWidget::~ObjPropertiesWidget()
{
}
