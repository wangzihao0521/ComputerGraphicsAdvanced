#include <MeGlWindow.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MeGlWindow meWindow;
	if (argc != 1)
		meWindow.tryImportFile(argv[1]);
	meWindow.show();
	app.exec();
	return 0;
}