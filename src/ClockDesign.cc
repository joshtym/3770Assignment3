#include <QtGui>
#include "ClockDesign.h"

ClockDesign::ClockDesign()
{
	interfaceDimensions = new QRect (200, 200, 100, 100);
}

ClockDesign::ClockDesign(int width, int height)
{
	int baseClockDiameter, x, y;
	
	if (width > height)
	{
		baseClockDiameter = height - 30;
		x = width / 2 - baseClockDiameter / 2;
		y = 5;
	}
	else
	{
		baseClockDiameter = width - 30;
		x = 5;
		y = height / 2 - baseClockDiameter / 2;
	}
	
	interfaceDimensions = new QRect(x, y, baseClockDiameter, baseClockDiameter);
}

ClockDesign::~ClockDesign()
{
}

void ClockDesign::updateSizeParameters(int newWidth, int newHeight)
{
	if (newWidth > newHeight)
	{
		interfaceDimensions->setWidth(newHeight - 30);
		interfaceDimensions->setHeight(newHeight - 30);
		interfaceDimensions->setX(newWidth / 2 - interfaceDimensions->width() / 2);
	}
	else
	{
		interfaceDimensions->setWidth(newWidth - 30);
		interfaceDimensions->setHeight(newWidth - 30);
		interfaceDimensions->setY(newHeight / 2 - interfaceDimensions->height() / 2);
	}
}

void ClockDesign::paintEvent(QPaintEvent* event)
{
	QPainter paint(this);
	paint.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	paint.drawEllipse(*interfaceDimensions);
}
