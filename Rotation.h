#ifndef ROTATION_H
#define ROTATION_H

#include "Point.h"

class Rotation
{
//private:
public:
	Point** tab0;
	Point** tab90;
	Point** tab180;
	Point** tab270;

	Point** generateTab90();
	Point** generateTab180();
	Point** generateTab270();


	Rotation();
	Point rotate(Point point, int degree);

	void printTab();
};

#endif