#include "FileWindow.h"

FileWindow* FileWindow::InstancePtr = nullptr;


FileWindow::FileWindow() 
{
	setMinimumSize(480, 135);
	resize(960, 270);
	
//	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	
	MainLayout = new QHBoxLayout;
	MainLayout->setAlignment(Qt::AlignTop);
	setLayout(MainLayout);
	setStyleSheet("background-color:white;");
	
	InstancePtr = this;
}

FileWindow::~FileWindow()
{
}

void FileWindow::AddFile(File * f)
{
	MainLayout->addWidget(f);
	AllFiles.push_back(f);
}

void FileWindow::_UnSelectAll()
{
	for (auto iter = AllFiles.begin(); iter != AllFiles.end(); ++iter)
	{
		(*iter)->_UnSelect();
	}
}

FileWindow * FileWindow::getInstance()
{
	if (InstancePtr)
		return InstancePtr;
	else {
		InstancePtr = new FileWindow;
		return InstancePtr;
	}
}

void FileWindow::mousePressEvent(QMouseEvent * e)
{
	_UnSelectAll();
}
