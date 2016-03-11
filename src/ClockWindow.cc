#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
	// Ensure we default the size to 400 x 400
	this->resize(400, 400);
	
	// Create our interface with size 400 x 400
	interface = new ClockDesign(400, 400);
	
	// Assign our central widget to be the clock itself
	centralWidget = interface;
	setCentralWidget(centralWidget);
	
	// Iinitialize our timer
	timer = new QTimer(this);
	
	// Create a connection for everytime the timer hits its timeout slot
	// to call our updateTime slot
	connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));
	
	// Start our timer with a timeout meter for ever 1000 ms = 1s
	timer->start(1000);
}

ClockWindow::~ClockWindow()
{
}

void ClockWindow::updateTime()
{
	// Get our date and time and update our clock design to take these new values into consideration
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
