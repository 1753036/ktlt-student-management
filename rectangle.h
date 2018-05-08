#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "misc.h"

#define BORDER_COLOR COLOR_STEAL

class Rectangle
{
	public:
		static void draw(int x, int y, int w, int h);
		static void draw(int w, int h);
	private:
		static char getCorner(int index);
		static void drawLine(int w);
};

#endif // RECTANGLE_H
