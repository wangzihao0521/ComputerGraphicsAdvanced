#include "File.h"
#include "FileWindow.h"
#include "QtGui\qmouseevent"
#include "MainWindow.h"

File::File(QIcon& Icon, std::string fname): QWidget(FileWindow::getInstance())
{
	icon = Icon;
	filename = fname;

	setMinimumSize(30, 30);
//	resize(35, 35);
	QVBoxLayout* MainLayout = new QVBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	MainLayout->setSizeConstraint(QLayout::SetFixedSize);
	setLayout(MainLayout);
	QPixmap pixmap = icon.pixmap(QSize(30, 30), QIcon::Active, QIcon::On);
	IconLabel = new QLabel;
	IconLabel->setPixmap(pixmap);
	IconLabel->setEnabled(!pixmap.isNull());
	QVBoxLayout* IconLayout = new QVBoxLayout;
	IconLayout->setAlignment(Qt::AlignRight);
	IconLabel->setLayout(IconLayout);
	MainLayout->addWidget(IconLabel);
	NameLabel = new QLabel;
	NameLabel->setText(QString::fromStdString(filename));
	MainLayout->addWidget(NameLabel);
//	setStyleSheet("background-color:black;");

}

File::~File()
{
}

void File::_Select()
{
	QPixmap pixmap = icon.pixmap(QSize(30, 30), QIcon::Selected, QIcon::On);
	IconLabel->setPixmap(pixmap);
	IconLabel->setEnabled(!pixmap.isNull());
}

void File::_UnSelect()
{
	QPixmap pixmap = icon.pixmap(QSize(30, 30), QIcon::Active, QIcon::On);
	IconLabel->setPixmap(pixmap);
	IconLabel->setEnabled(!pixmap.isNull());
}

void File::enterEvent(QEvent* e)
{
	
}

void File::leaveEvent(QEvent * e)
{
	
}

void File::mousePressEvent(QMouseEvent * e)
{
	FileWindow::getInstance()->_UnSelectAll();
	_Select();
}

void File::mouseReleaseEvent(QMouseEvent * e)
{
	if (MainWindow::getInstance()->childAt(e->globalPos()) == MainWindow::getInstance()->getScene())
	{
		this->_PutInScene(e);
	}
}
