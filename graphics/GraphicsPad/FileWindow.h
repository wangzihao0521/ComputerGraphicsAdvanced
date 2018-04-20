#pragma once
#include "File.h"

class FileWindow : public QWidget
{
public :
	FileWindow();
	~FileWindow();

	void AddFile(File* f);
	void _UnSelectAll();

	static FileWindow* getInstance();

private:
	QHBoxLayout* MainLayout;

	static FileWindow* InstancePtr;

protected:
	void mousePressEvent(QMouseEvent* e);

	std::list<File*> AllFiles;
};

