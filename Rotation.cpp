
#include "Rotation.h"
#include <iostream>


Point** Rotation::generateTab90()
{
	int x1 = 0;
	int y1 = 0;

	Point** tab = 0;
	tab = new Point * [4];

	for (int y = 3; y >= 0; --y)
	{
		y1 = 0;
		tab[x1] = new Point[4];

		for (int x = 0; x < 4; ++x)
		{
			tab[x1][y1] = Point(x, y);
			y1++;
		}
		x1++;
	}

	return tab;
}

Point** Rotation::generateTab180()
{
	int x1 = 0;
	int y1 = 0;

	Point** tab = 0;
	tab = new Point * [4];

	for (int x = 3; x >= 0; --x)
	{
		y1 = 0;
		tab[x1] = new Point[4];

		for (int y = 3; y >= 0; --y)
		{
			tab[x1][y1] = Point(x, y);
			y1++;
		}
		x1++;
	}

	return tab;
}


Point** Rotation::generateTab270()
{
	int x1 = 0;
	int y1 = 0;

	Point** tab = 0;
	tab = new Point * [4];

	for (int y = 0; y < 4; ++y)
	{
		y1 = 0;
		tab[x1] = new Point[4];

		for (int x = 3; x >= 0; --x)
		{
			tab[x1][y1] = Point(x, y);
			y1++;
		}
		x1++;
	}

	return tab;
}


Rotation::Rotation()
{
	tab90 = generateTab90();
	tab180 = generateTab180();
	tab270 = generateTab270();
}

void Rotation::printTab()
{
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << tab90[x][y].getX() << tab90[x][y].getY() << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << tab90[x][y].getX() << tab90[x][y].getY() << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			std::cout << tab90[x][y].getX() << tab90[x][y].getY() << "  ";
		}
		std::cout << std::endl;
	}
}

Point Rotation::rotate(Point point, int degree)
{
	if (degree == 0)
	{
		return Point(point.getX(), point.getY());
	}
	if (degree == 90)
	{
		return tab90[point.getX()][point.getY()];
	}
	else if (degree == 180)
	{
		return tab180[point.getX()][point.getY()];
	}
	else if (degree == 270)
	{
		return tab270[point.getX()][point.getY()];
	}
	else
	{
		return Point();
	}
}

