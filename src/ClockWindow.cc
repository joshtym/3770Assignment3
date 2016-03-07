#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
	this->resize(600, 600);
	interface = new ClockDesign(600, 600);
	interface->updateSizeParameters(600, 600);
	
	centralWidget = interface;
	setCentralWidget(centralWidget);
	
	const QString text = getTime();
	time = new QLabel(text);
	
	timer = new QTimer(this);
	
	connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
	timer->start();
}

ClockWindow::~ClockWindow()
{
}

void ClockWindow::showTime()
{
	const QString text = getTime();
	time->setText(text);
}

QString ClockWindow::getTime()
{
	QTime time = QTime::currentTime();
	QString timeText = time.toString("hh : mm : ss");
	return timeText;
}

void ClockWindow::resizeEvent(QResizeEvent* e)
{
	interface->updateSizeParameters(this->geometry().width(), this->geometry().height());
}
