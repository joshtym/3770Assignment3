#include <QtGui>
#include <cmath>
#include <iostream>
#include "ClockDesign.h"

ClockDesign::ClockDesign()
{
	PI = 3.1415926535897932384626;
	currentHour = 0;
	currentMinute = 0;
	isTransparent = false;
	
	interfaceDimensions = new QRect (200, 200, 100, 100);
	
	innerClockObjects.clear();
	clockMonthObjects.clear();
	
	for (int i = 0; i < 59; ++i)
		innerClockObjects.push_back(new QRect);
	
	for (int i = 0; i < 12; ++i)
		clockMonthObjects.push_back(new QRect);
	
	assignClockObjectDimensions();
}

ClockDesign::ClockDesign(int width, int height)
{
	PI = 3.1415926535897932384626;
	currentHour = 0;
	currentMinute = 0;
	isTransparent = false;
	
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
	clockMonthObjects.clear();
	
	for (int i = 0; i < 60; ++i)
		innerClockObjects.push_back(new QRect);
		
	for (int i = 0; i < 12; ++i)
		clockMonthObjects.push_back(new QRect);
		
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

void ClockDesign::clockUpdated(int hour, int minute, int month, int day)
{
	if (hour >= 12)
		currentHour = hour - 12;
	else
		currentHour = hour;
	
	currentMinute = minute;
	currentMonth = month;
	currentDay = day;
	update();
}

void ClockDesign::paintEvent(QPaintEvent* event)
{
	QPainter paint(this);
	paint.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	paint.setPen(QPen(Qt::black, 2, Qt::SolidLine));
	paint.drawEllipse(*interfaceDimensions);
		
	for (int i = 0; i < 60; ++i)
	{
		if (i == currentHour * 5)
		{
			if (isTransparent)
			{
				paint.setPen(QPen(Qt::white, 0, Qt::SolidLine));
				paint.setBrush(QBrush(Qt::blue, Qt::NoBrush));
				isTransparent = false;
			}
			else
			{
				paint.setPen(QPen(Qt::white, 2, Qt::SolidLine));
				paint.setBrush(QBrush(Qt::white, Qt::SolidPattern));
				isTransparent = true;
			}
		}
		else if (i <= currentMinute)
		{
			if (i % 5 == 0)
			{
				paint.setPen(QPen(Qt::white, 2, Qt::SolidLine));
				paint.setBrush(QBrush(Qt::white, Qt::SolidPattern));
			}
			else
			{
				paint.setPen(QPen(Qt::blue, 2, Qt::SolidLine));
				paint.setBrush(QBrush(Qt::blue, Qt::SolidPattern));
			}
		}
		else
		{
			paint.setPen(QPen(Qt::white, 0, Qt::SolidLine));
			paint.setBrush(QBrush(Qt::white, Qt::NoBrush));
		}
		
		paint.drawEllipse(*innerClockObjects[i]);
	}
	
	for (int i = 0; i < 12; ++i)
	{
		if (i < currentMonth)
		{
			paint.setPen(QPen(Qt::white, 2, Qt::SolidLine));
			paint.setBrush(QBrush(Qt::white, Qt::SolidPattern));
		}
		else
		{
			paint.setPen(QPen(Qt::white, 0, Qt::SolidLine));
			paint.setBrush(QBrush(Qt::white, Qt::NoBrush));
		}
		paint.drawEllipse(*clockMonthObjects[i]);
	}
}

void ClockDesign::assignClockObjectDimensions()
{
	int hourRadius, minuteRadius, monthRadius, hourMidX, hourMidY, minutehourMidX, minutehourMidY, monthMidX, monthMidY, counter;
	
	for (int i = 0; i < 60; ++i)
	{
		if (i % 5 == 0)
		{
			innerClockObjects[i]->setWidth(interfaceDimensions->width() / 20);
			innerClockObjects[i]->setHeight(interfaceDimensions->height() / 20);
			clockMonthObjects[i / 5]->setWidth(interfaceDimensions->width() / 30);
			clockMonthObjects[i / 5]->setHeight(interfaceDimensions->height() / 30);
		}
		else
		{
			innerClockObjects[i]->setWidth(interfaceDimensions->width() / 50);
			innerClockObjects[i]->setHeight(interfaceDimensions->height() / 50);
		}
	}
	
	hourRadius = interfaceDimensions->height() / 2 - interfaceDimensions->height() / 80 - innerClockObjects[0]->height() / 2;
	minuteRadius = interfaceDimensions->height() / 2 - interfaceDimensions->height() / 40 - innerClockObjects[1]->height() / 2;
	monthRadius = interfaceDimensions->height() / 2 - interfaceDimensions->height() / 3 - clockMonthObjects[0]->height() / 2;
	hourMidX = interfaceDimensions->x() + interfaceDimensions->width() / 2 - innerClockObjects[0]->width() / 2;
	hourMidY = interfaceDimensions->y() + interfaceDimensions->height() / 80 + hourRadius;
	minutehourMidX = interfaceDimensions->x() + interfaceDimensions->width() / 2 - innerClockObjects[1]->width() / 2;
	minutehourMidY = interfaceDimensions->y() + interfaceDimensions->height() / 40 + minuteRadius;
	monthMidX = interfaceDimensions->x() + interfaceDimensions->width() / 2 - clockMonthObjects[0]->width() / 2;
	monthMidY = interfaceDimensions->y() + interfaceDimensions->height() / 3 + monthRadius;
	counter = 15;
	
	for (int i = 0; i < 60; i++)
	{
		if (i % 5 == 0)
		{
			innerClockObjects[i]->setX(hourMidX + (hourRadius * cos(counter * PI / 30)));
			innerClockObjects[i]->setY(hourMidY - (hourRadius * sin(counter * PI / 30)));
			clockMonthObjects[i / 5]->setX(monthMidX + (monthRadius * cos(counter * PI / 30)));
			clockMonthObjects[i / 5]->setY(monthMidY - (monthRadius * sin(counter * PI / 30)));
		}
		else
		{
			innerClockObjects[i]->setX(minutehourMidX + (minuteRadius * cos(counter * PI / 30)));
			innerClockObjects[i]->setY(minutehourMidY - (minuteRadius * sin(counter * PI / 30)));
		}
		if (--counter < 0)
			counter = 59;
	}
}
