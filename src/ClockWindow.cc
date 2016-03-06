#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
	/*QDesktopWidget dw;
	QRect mainScreenSize = dw.availableGeometry(dw.primaryScreen());
	
	int x = mainScreenSize.width() * 0.5;
	int y = mainScreenSize.height() * 0.5;
	
	this->setFixedSize(x, y);*/
	this->resize(600, 400);
	interface = new ClockDesign(600, 400);
	interface->resize(QSize(600, 400));
	
	QWidget* centralWidget = new QWidget;
	
	QVBoxLayout* clockInterface = new QVBoxLayout;
	
	const QString text = getTime();
	time = new QLabel(text);
	
	timer = new QTimer(this);
	
	setCentralWidget(centralWidget);

	//clockInterface->addWidget(time);
	
	//primaryDisplayUnit->addLayout(clockInterface);
	clockInterface->addWidget(interface);
	
	centralWidget->setLayout(clockInterface);
	
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
