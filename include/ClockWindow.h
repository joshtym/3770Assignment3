#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QMainWindow>

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
		QString getTime();
		QPushButton* quitButton;
		QTimer* timer;
		QLabel* time;
};
#endif
