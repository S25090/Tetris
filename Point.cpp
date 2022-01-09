#include "Point.h"
#include <iostream>


Point::Point(int x, int y) : x{ x }, y{ y }
{
}

Point::Point() : x{ 0 }, y{ 0 }
{
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

