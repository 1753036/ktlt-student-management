#include "rectangle.h"

void Rectangle::draw(int w, int h)
{
	setColor(COLOR_BLACK, BORDER_COLOR);
	w *= 2;
	std::cout << getCorner(0);
	for (int i = 0; i < (w - 1); ++i)
		std::cout << getCorner(4);
	std::cout << getCorner(1) << std::endl;

	for (int i = 0; i < (h - 2); ++i)
		drawLine(w);

	std::cout << getCorner(3);
	for (int i = 0; i < (w - 1); ++i)
		std::cout << getCorner(4);
	std::cout << getCorner(2) << std::endl;
	setColor(COLOR_BLACK, COLOR_DEFAULT);
}

char Rectangle::getCorner(int index)
{
	switch(index)
	{
		case 0: return char(201); break;
		case 1: return char(187); break;
		case 2: return char(188); break;
		case 3: return char(200); break;
		case 4: return char(205); break;
		case 5: return char(186); break;
	}
	return 0;
}

void Rectangle::drawLine(int w)
{
	std::cout << getCorner(5);
	for (int i = 0; i < (w - 1); ++i)
		std::cout << " ";
	std::cout << getCorner(5) << std::endl;
}
