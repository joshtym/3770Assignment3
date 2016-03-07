#ifndef CLOCKDESIGN_H
#define CLOCKDESIGN_H

#include <QWidget>
#include <vector>

class ClockDesign : public QWidget
{
	Q_OBJECT
	
	public:
		ClockDesign();
		ClockDesign(int, int);
		~ClockDesign();
		void updateSizeParameters(int, int);
		void clockUpdated(int, int, int, int);
		
	protected:
		void paintEvent(QPaintEvent*);
		
	private:
		void assignClockObjectDimensions();
		double PI;
		bool isTransparent;
		QRect* interfaceDimensions;
		std::vector<QRect*> innerClockObjects;
		std::vector<QRect*> clockMonthObjects;
		int currentMinute;
		int currentHour;
		int currentMonth;
		int currentDay;
};
#endif
