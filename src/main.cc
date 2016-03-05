#include <QtGui>
#include "ClockWindow.h"

int main(int argc, char** argv)
{
	QApplication clockApplication(argc, argv);
	
	ClockWindow cWindow;
	cWindow.setWindowTitle("Clock Interface");
	cWindow.show();
	
	return clockApplication.exec();
}
