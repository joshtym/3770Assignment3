#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
	this->resize(400, 400);
	interface = new ClockDesign(400, 400);
	interface->updateSizeParameters(400, 400);
	
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
	QDate date = QDate::currentDate();
	interface->clockUpdated(time.hour(), time.minute(), date.month(), date.day());
}

void ClockWindow::resizeEvent(QResizeEvent* e)
{
	// FOR SOME REASON, WHEN MAXIMIZING, THIS NEEDS TO BE CALLED THREE TIMES TO PROPERLY WORK
	interface->updateSizeParameters(this->geometry().width(), this->geometry().height());
	interface->updateSizeParameters(this->geometry().width(), this->geometry().height());
	interface->updateSizeParameters(this->geometry().width(), this->geometry().height());
}
