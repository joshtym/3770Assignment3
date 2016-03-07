#include <QtGui>
#include <cmath>
#include "ClockDesign.h"

ClockDesign::ClockDesign()
{
	PI = 3.1415926535897932384626;
	interfaceDimensions = new QRect (200, 200, 100, 100);
	
	innerClockObjects.clear();
	
	for (int i = 0; i < 12; ++i)
		innerClockObjects.push_back(new QRect);
	
	assignClockObjectDimensions();
}

ClockDesign::ClockDesign(int width, int height)
{
	PI = 3.1415926535897932384626;
	
	int baseClockDiameter, x, y;
	
	if (width > height)
	{
		baseClockDiameter = height - 10;
		x = width / 2 - baseClockDiameter / 2;
		y = 5;
	}
	else
	{
		baseClockDiameter = width - 10;
		x = 5;
		y = height / 2 - baseClockDiameter / 2;
	}
	
	interfaceDimensions = new QRect(x, y, baseClockDiameter, baseClockDiameter);
	
	innerClockObjects.clear();
	
	for (int i = 0; i < 12; ++i)
		innerClockObjects.push_back(new QRect);
		
	assignClockObjectDimensions();
}

ClockDesign::~ClockDesign()
{
}

void ClockDesign::updateSizeParameters(int newWidth, int newHeight)
{
	if (newWidth > newHeight)
	{
		interfaceDimensions->setWidth(newHeight - 10);
		interfaceDimensions->setHeight(newHeight - 10);
		interfaceDimensions->setX(newWidth / 2 - interfaceDimensions->width() / 2);
		interfaceDimensions->setY(5);
	}
	else
	{
		interfaceDimensions->setWidth(newWidth - 10);
		interfaceDimensions->setHeight(newWidth - 10);
		interfaceDimensions->setX(5);
		interfaceDimensions->setY(newHeight / 2 - interfaceDimensions->height() / 2);
	}
	
	assignClockObjectDimensions();
}

void ClockDesign::paintEvent(QPaintEvent* event)
{
	QPainter paint(this);
	paint.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	paint.setPen(QPen(Qt::black, 2, Qt::SolidLine));
	paint.drawEllipse(*interfaceDimensions);
	
	paint.setPen(QPen(Qt::white, 2, Qt::SolidLine));
	paint.setBrush(QBrush(Qt::white, Qt::SolidPattern));
	
	for (int i = 0; i < 12; ++i)
		paint.drawEllipse(*innerClockObjects[i]);
}

void ClockDesign::assignClockObjectDimensions()
{
	int innerRadius;
	
	innerClockObjects[0]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[0]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[0]->setX(interfaceDimensions->x() + interfaceDimensions->width() / 2 - innerClockObjects[0]->width() / 2);
	innerClockObjects[0]->setY(interfaceDimensions->y() + interfaceDimensions->height() / 80);
	
	innerRadius = (interfaceDimensions->y() + interfaceDimensions->height() / 2) - (innerClockObjects[0]->y() + innerClockObjects[0]->height() / 2);
	
	innerClockObjects[1]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[1]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[1]->setX(innerClockObjects[0]->x() + (innerRadius * cos(PI / 3)));
	innerClockObjects[1]->setY(innerClockObjects[0]->y() + (innerRadius - (innerRadius * sin(PI / 3))));
	
	innerClockObjects[2]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[2]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[2]->setX(innerClockObjects[0]->x() + (innerRadius * cos(PI / 6)));
	innerClockObjects[2]->setY(innerClockObjects[0]->y() + (innerRadius - (innerRadius * sin(PI / 6))));
	
	innerClockObjects[3]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[3]->setHeight(interfaceDimensions->height() / 20);
	//innerClockObjects[3]->setX(interfaceDimensions->x() + interfaceDimensions->width() - innerClockObjects[3]->width() - interfaceDimensions->width() / 80);
	//innerClockObjects[3]->setY(interfaceDimensions->y() + interfaceDimensions->height() / 2 - innerClockObjects[3]->height() / 2);
	innerClockObjects[3]->setX(innerClockObjects[0]->x() + innerRadius);
	innerClockObjects[3]->setY(innerClockObjects[0]->y() + innerRadius);
	
	innerClockObjects[4]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[4]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[4]->setX(innerClockObjects[0]->x() + (innerRadius * cos(11 * PI / 6)));
	innerClockObjects[4]->setY(innerClockObjects[0]->y() + innerRadius - (innerRadius * sin(11 * PI / 6)));
	
	innerClockObjects[5]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[5]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[5]->setX(innerClockObjects[0]->x() + (innerRadius * cos(5 * PI / 3)));
	innerClockObjects[5]->setY(innerClockObjects[0]->y() + innerRadius - (innerRadius * sin(5 * PI / 3)));
	
	innerClockObjects[6]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[6]->setHeight(interfaceDimensions->height() / 20);
	//innerClockObjects[6]->setX(interfaceDimensions->x() + interfaceDimensions->width() / 2 - innerClockObjects[6]->width() / 2);
	//innerClockObjects[6]->setY(interfaceDimensions->height() - innerClockObjects[6]->height() - interfaceDimensions->height() / 80);
	innerClockObjects[6]->setX(innerClockObjects[0]->x());
	innerClockObjects[6]->setY(innerClockObjects[0]->y() + 2 * innerRadius);
	
	innerClockObjects[7]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[7]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[7]->setX(innerClockObjects[0]->x() + (innerRadius * cos(4 * PI / 3)));
	innerClockObjects[7]->setY(innerClockObjects[0]->y() + innerRadius - (innerRadius * sin(4 * PI / 3)));
	
	innerClockObjects[8]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[8]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[8]->setX(innerClockObjects[0]->x() + (innerRadius * cos(7 * PI / 6)));
	innerClockObjects[8]->setY(innerClockObjects[0]->y() + innerRadius - (innerRadius * sin(7 * PI / 6)));
	
	innerClockObjects[9]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[9]->setHeight(interfaceDimensions->height() / 20);
	//innerClockObjects[9]->setX(interfaceDimensions->x() + interfaceDimensions->width() / 80);
	//innerClockObjects[9]->setY(interfaceDimensions->y() + interfaceDimensions->height() / 2 - innerClockObjects[9]->height() / 2);
	innerClockObjects[9]->setX(innerClockObjects[0]->x() - innerRadius);
	innerClockObjects[9]->setY(innerClockObjects[0]->y() + innerRadius);
	
	innerClockObjects[10]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[10]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[10]->setX(innerClockObjects[0]->x() + (innerRadius * cos(5 * PI / 6)));
	innerClockObjects[10]->setY(innerClockObjects[0]->y() + innerRadius - (innerRadius * sin(5 * PI / 6)));
	
	innerClockObjects[11]->setWidth(interfaceDimensions->width() / 20);
	innerClockObjects[11]->setHeight(interfaceDimensions->height() / 20);
	innerClockObjects[11]->setX(innerClockObjects[0]->x() + (innerRadius * cos(2 * PI / 3)));
	innerClockObjects[11]->setY(innerClockObjects[0]->y() + innerRadius - (innerRadius * sin(2 * PI / 3)));
}
