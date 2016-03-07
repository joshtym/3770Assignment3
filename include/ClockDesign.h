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
		
	protected:
		void paintEvent(QPaintEvent*);
		
	private:
		void assignClockObjectDimensions();
		double PI;
		QRect* interfaceDimensions;
		std::vector<QRect*> innerClockObjects;
};
#endif
