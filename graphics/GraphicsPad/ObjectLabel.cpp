#include "ObjectLabel.h"
#include "Object.h"
#include "SceneObjManager.h"

ObjectLabel::ObjectLabel(Object * obj)
{
	object = obj;

	QHBoxLayout* MainLayout = new QHBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
//	MainLayout->setSizeConstraint(QLayout::SetMinimumSize);
	setLayout(MainLayout);
	MainLayout->setSpacing(0);
	MainLayout->setMargin(0);

	label = new QLabel;
	label->setText(QString::fromStdString(object->getName()));
	label->setEnabled(true);
	label->setAutoFillBackground(true);
	MainLayout->addWidget(label);
	label->setStyleSheet("background-color:gray;color : black");

}

ObjectLabel::~ObjectLabel()
{
}

void ObjectLabel::_UnSelect()
{
	object->Unselect();
}

void ObjectLabel::_Select()
{
	object->Select();
}

void ObjectLabel::SetSelected(bool b)
{
	if (b)
		label->setStyleSheet("background-color:gray;color : black");
	else
		label->setStyleSheet("background-color:white;color : black");
}

void ObjectLabel::mousePressEvent(QMouseEvent * e)
{
	SceneObjManager::getInstance()->_UnSelectAll();
	_Select();
}
