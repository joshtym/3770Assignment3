#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QMainWindow>
#include "ClockDesign.h"

class QPushButton;
class QTime;
class QTimer;
class QLabel;

class ClockWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		ClockWindow();
		~ClockWindow();
	private slots:
		void showTime();
		
	private:
		ClockDesign* interface;
		void resizeEvent(QResizeEvent*);
		QString getTime();
		QTimer* timer;
		QLabel* time;
};
#endif
