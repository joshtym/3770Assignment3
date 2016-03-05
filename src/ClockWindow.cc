#include <QtGui>
#include "ClockWindow.h"

ClockWindow::ClockWindow()
{
	QFont font1("Arial", 18);
	QWidget* centralWidget = new QWidget;
	
	quitButton = new QPushButton("Quit");
	
	QHBoxLayout* buttons = new QHBoxLayout;
	QHBoxLayout* clockInterface = new QHBoxLayout;
	QVBoxLayout* primaryDisplayUnit = new QVBoxLayout;
	
	const QString text = getTime();
	time = new QLabel(text);
	
	timer = new QTimer(this);
	
	setCentralWidget(centralWidget);
	
	quitButton->setFont(font1);
	buttons->addWidget(quitButton);
	clockInterface->addWidget(time);
	
	primaryDisplayUnit->addLayout(clockInterface);
	primaryDisplayUnit->addLayout(buttons);
	
	centralWidget->setLayout(primaryDisplayUnit);
	
	connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
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

