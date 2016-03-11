#ifndef CLOCKDESIGN_H
#define CLOCKDESIGN_H

#include <QWidget>
#include <vector>

/// Class that handles the interface design
/*
 * Class has all the painter functionality built in to ensure
 * our interface is drawn to the screen properly with appropriate
 * dimensions and jazz
 */
class ClockDesign : public QWidget
{
	// Meta object compiler macro
	Q_OBJECT
	
	public:
		// Default constructor
		ClockDesign();
		
		// Constructor that takes in width and height of window
		ClockDesign(int, int);
		
		// Destructor of class
		~ClockDesign();
		
		// Function that handles resizing events
		void updateSizeParameters(int, int);
		
		// Function that handles clock update events
		void clockUpdated(int, int, int, int);
		
	protected:
		// Function to handle the painting of our interface
		void paintEvent(QPaintEvent*);
		
	private:
		// Private helper function to assign our clock dimensions for
		// interface, the outer LEDs, and the inner LEDs
		void assignClockObjectDimensions();
		
		// Private helper function to convert given day to a string
		void convertDayToString(int);
		
		// Variable for PI to do our unit circle calculations
		double PI;
		
		// Private variable to handle the blinking hour LED
		bool isTransparent;
		
		// Our dimensions for our interface (black circle), each inner
		// clock object (outer LEDS), inner Month LEDS, and date
		QRect* interfaceDimensions;
		std::vector<QRect*> innerClockObjects;
		std::vector<QRect*> clockMonthObjects;
		QRect* textLocation;
		
		// Private variables
		int currentMinute;
		int currentHour;
		int currentMonth;
		QString currentDay;
};
#endif
