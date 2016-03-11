#ifndef CLOCKWINDOW_H
#define CLOCKWINDOW_H

#include <QMainWindow>
#include "ClockDesign.h"

// Forward declarations
class QTime;
class QTimer;

/// Class for handling the main window of the program
/*
 * Class does the grunt work to provide an initial place to being
 * drawing our interface. Includes functionality for resizing the
 * window
 */
class ClockWindow : public QMainWindow
{
	// Meta object compiler macro
	Q_OBJECT
	
	public:
		// Default constructor for the class
		ClockWindow();
		
		// Destructor for the class
		~ClockWindow();
		
	private slots:
		// Slot that is called everytime we need to update our clock
		void updateTime();
		
	private:
		// Function that handles resizing of the window in QT
		void resizeEvent(QResizeEvent*);
		
		// Private data member for the clock design itself
		ClockDesign* interface;
		
		// Private variable for our timer
		QTimer* timer;
		
		// Our central widget of the window
		QWidget* centralWidget;
};
#endif
