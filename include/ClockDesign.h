#ifndef CLOCKDESIGN_H
#define CLOCKDESIGN_H

#include <QWidget>

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
		QRect* interfaceDimensions;
};
#endif
