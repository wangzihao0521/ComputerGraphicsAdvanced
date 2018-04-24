#include "Texture.h"
#include "ObjPropertiesManager.h"
#include <QtGui\qmouseevent>

void Texture::_PutInScene(QMouseEvent * e)
{
}

void Texture::_PutInObjProperties(QMouseEvent * e)
{
	QPoint point = ObjPropertiesManager::getInstance()->mapFromGlobal(e->globalPos());
	ObjPropertiesManager::getInstance()->Try_ChangeTex(point,this);

}

void Texture::_DisplayProperties()
{
	ObjPropertiesManager::getInstance()->DisplayTexture(this);
}
