#include <QtGui>
#include <cmath>
#include <iostream>
#include "ClockDesign.h"

ClockDesign::ClockDesign()
{
	// Assign our default values
	PI = 3.1415926535897932384626;
	currentHour = 0;
	currentMinute = 0;
	isTransparent = false;
	currentDay = "";
	
	// Create our dimensions for all of our objects
	interfaceDimensions = new QRect (200, 200, 100, 100);
	textLocation = new QRect;
	
	// Ensure empty vectors before creating them
	innerClockObjects.clear();
	clockMonthObjects.clear();
	
	for (int i = 0; i < 59; ++i)
		innerClockObjects.push_back(new QRect);
	
	for (int i = 0; i < 12; ++i)
		clockMonthObjects.push_back(new QRect);
	
	// Assign our clock dimensions dependent on what our interface
	// dimensions are
	assignClockObjectDimensions();
}

ClockDesign::ClockDesign(int width, int height)
{
	// Assign our default values
	PI = 3.1415926535897932384626;
	currentHour = 0;
	currentMinute = 0;
	isTransparent = false;
	currentDay = "";
	
	// Private helper variables
	int baseClockDiameter, x, y;
	
	// Assign our helper variables dependent on whether height or width is greater
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
	
	// Create dimensions for all of our objects
	interfaceDimensions = new QRect(x, y, baseClockDiameter, baseClockDiameter);
	textLocation = new QRect;
	
	// Clear our vectors before instantiating new objects
	innerClockObjects.clear();
	clockMonthObjects.clear();
	
	for (int i = 0; i < 60; ++i)
		innerClockObjects.push_back(new QRect);
		
	for (int i = 0; i < 12; ++i)
		clockMonthObjects.push_back(new QRect);
	
	// Assign our inner clock dimensions dependent on width and height of interface
	assignClockObjectDimensions();
}

ClockDesign::~ClockDesign()
{
}

void ClockDesign::updateSizeParameters(int newWidth, int newHeight)
{
	// Update our parameters based on whether the newWidth or newHeight is bigger
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
	// We don't want to worry about 24 hour time
	if (hour >= 12)
		currentHour = hour - 12;
	else
		currentHour = hour;
	
	currentMinute = minute;
	currentMonth = month;
	
	// Assign our QString value to the current day
	convertDayToString(day);
	
	// Update the Widget!
	update();
}

void ClockDesign::paintEvent(QPaintEvent* event)
{
	// Create a paint
	QPainter paint(this);
	QFont font = paint.font();
	
	// Set our paint brush and pen to draw the back interface (black circle)
	paint.setBrush(QBrush(Qt::black, Qt::SolidPattern));
	paint.setPen(QPen(Qt::black, 2, Qt::SolidLine));
	paint.drawEllipse(*interfaceDimensions);
	
	// Iterate through to draw the 60 elements of the outer circle LEDS	
	for (int i = 0; i < 60; ++i)
	{
		// Handle the blinking of the currentHour LED
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
			// Handle the current minute and assign brushes
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
	
	// Draw the interior of the clock (Month portion)
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
	
	// Draw the date
	font.setPointSize(interfaceDimensions->width() / 10);
	paint.setFont(font);
	paint.drawText(*textLocation, currentDay);
}

void ClockDesign::assignClockObjectDimensions()
{
	// Helper variables for calculations
	int hourRadius, minuteRadius, monthRadius, hourMidX, hourMidY, minutehourMidX, minutehourMidY, monthMidX, monthMidY, counter;
	
	// Assign the width and heights of ever object
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
	
	// Calculate circular radius and mids based on sizes
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
	
	textLocation->setX(monthMidX + ((monthRadius - monthRadius / 2) * cos(3 * PI / 4)));
	textLocation->setY(monthMidY - ((monthRadius - monthRadius / 2) * sin(3 * PI / 4)));
	textLocation->setWidth(monthRadius * 2);
	textLocation->setHeight(monthRadius * 2);
	
	// Calculate drawing x and y values for every object
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

void ClockDesign::convertDayToString(int day)
{
	currentDay.clear();
	currentDay = "";
	
	switch(day / 10)
	{
		case 0:
			currentDay.append("0");
			break;
		case 1:
			currentDay.append("1");
			break;
		case 2:
			currentDay.append("2");
			break;
		case 3:
			currentDay.append("3");
			break;
		case 4:
			currentDay.append("4");
			break;
		case 5:
			currentDay.append("5");
			break;
		case 6:
			currentDay.append("6");
			break;
		case 7:
			currentDay.append("7");
			break;
		case 8:
			currentDay.append("8");
			break;
		case 9:
			currentDay.append("9");
			break;
		default:
			break;
	}
	
	switch(day % 10)
	{
		case 0:
			currentDay.append("0");
			break;
		case 1:
			currentDay.append("1");
			break;
		case 2:
			currentDay.append("2");
			break;
		case 3:
			currentDay.append("3");
			break;
		case 4:
			currentDay.append("4");
			break;
		case 5:
			currentDay.append("5");
			break;
		case 6:
			currentDay.append("6");
			break;
		case 7:
			currentDay.append("7");
			break;
		case 8:
			currentDay.append("8");
			break;
		case 9:
			currentDay.append("9");
			break;
		default:
			break;
	}
}
