#include "MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow meWindow;
	meWindow.show();
	app.exec();

//	_CrtDumpMemoryLeaks();

	return 0;
}