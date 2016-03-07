#include <QtGui>
#include <cmath>
#include <iostream>
#include "ClockDesign.h"

ClockDesign::ClockDesign()
{
	PI = 3.1415926535897932384626;
	currentHour = 0;
	currentMinute = 0;
	
	interfaceDimensions = new QRect (200, 200, 100, 100);
	
	innerClockObjects.clear();
	
	for (int i = 0; i < 59; ++i)
		innerClockObjects.push_back(new QRect);
	
	assignClockObjectDimensions();
}

ClockDesign::ClockDesign(int width, int height)
{
	PI = 3.1415926535897932384626;
	currentHour = 0;
	currentMinute = 0;
	
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
	
	for (int i = 0; i < 60; ++i)
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

void ClockDesign::clockUpdated(int hour, int minute)
{
	if (hour >= 12)
		currentHour = hour - 12;
	
	currentMinute = minute;
	update();
}

void ClockDesign::paintEvent(QPaintEvent* event)
{
	QPainter paint(this);
	paint.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	paint.setPen(QPen(Qt::black, 2, Qt::SolidLine));
	paint.drawEllipse(*interfaceDimensions);
	
	for (int i = 0; i < 60; i++)
	{
		if (i == currentHour * 5 || i == currentMinute)
		{
			paint.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
			paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
		}
		else
		{
			paint.setPen(QPen(Qt::white, 2, Qt::SolidLine));
			paint.setBrush(QBrush(Qt::white, Qt::SolidPattern));
		}
		
		paint.drawEllipse(*innerClockObjects[i]);
	}
}

void ClockDesign::assignClockObjectDimensions()
{
	int innerRadius, innerRadiusSmaller, midX, midY, midXSmaller, midYSmaller, counter;
	
	for (int i = 0; i < 60; ++i)
	{
		if (i % 5 == 0)
		{
			innerClockObjects[i]->setWidth(interfaceDimensions->width() / 20);
			innerClockObjects[i]->setHeight(interfaceDimensions->height() / 20);
		}
		else
		{
			innerClockObjects[i]->setWidth(interfaceDimensions->width() / 50);
			innerClockObjects[i]->setHeight(interfaceDimensions->height() / 50);
		}
	}
	
	innerRadius = interfaceDimensions->height() / 2 - interfaceDimensions->height() / 80 - innerClockObjects[0]->height() / 2;
	innerRadiusSmaller = interfaceDimensions->height() / 2 - interfaceDimensions->height() / 40 - innerClockObjects[1]->height() / 2;
	midX = interfaceDimensions->x() + interfaceDimensions->width() / 2 - innerClockObjects[0]->width() / 2;
	midY = interfaceDimensions->y() + interfaceDimensions->height() / 80 + innerRadius;
	midXSmaller = interfaceDimensions->x() + interfaceDimensions->width() / 2 - innerClockObjects[1]->width() / 2;
	midYSmaller = interfaceDimensions->y() + interfaceDimensions->height() / 40 + innerRadiusSmaller;
	counter = 15;
	
	for (int i = 0; i < 60; i++)
	{
		if (i % 5 == 0)
		{
			innerClockObjects[i]->setX(midX + (innerRadius * cos(counter * PI / 30)));
			innerClockObjects[i]->setY(midY - (innerRadius * sin(counter * PI / 30)));
		}
		else
		{
			innerClockObjects[i]->setX(midXSmaller + (innerRadiusSmaller * cos(counter * PI / 30)));
			innerClockObjects[i]->setY(midYSmaller - (innerRadiusSmaller * sin(counter * PI / 30)));
		}
		if (--counter < 0)
			counter = 59;
	}
}
