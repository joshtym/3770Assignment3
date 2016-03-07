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
		void updateTime();
		
	private:
		ClockDesign* interface;
		void resizeEvent(QResizeEvent*);
		QTimer* timer;
		QWidget* centralWidget;
};
#endif
