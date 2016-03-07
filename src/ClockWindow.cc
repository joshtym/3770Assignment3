#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
	this->resize(600, 600);
	interface = new ClockDesign(600, 600);
	interface->updateSizeParameters(600, 600);
	
	centralWidget = interface;
	setCentralWidget(centralWidget);
	
	timer = new QTimer(this);
	
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	timer->start(1000);
}

ClockWindow::~ClockWindow()
{
}

void ClockWindow::updateTime()
{
	QTime time = QTime::currentTime();
	interface->clockUpdated(time.hour(), time.minute());
}

void ClockWindow::resizeEvent(QResizeEvent* e)
{
	interface->updateSizeParameters(this->geometry().width(), this->geometry().height());
}
