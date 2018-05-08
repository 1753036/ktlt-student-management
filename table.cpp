#include "table.h"

Table::Table(std::string title, int rows, int cols)
{
	getConsoleSize(_height, _width);

	_title = title;
	_rows = rows;
	_cols = cols;
	_spacing = _width / _cols;

	_cols -= 1;
	_width -= 2;
}

Table::~Table()
{
	_seps.clear();
	_title.clear();
}

void Table::show()
{
	CLEAR_CMD();
	setColor(COLOR_BLACK, TABLE_BORDER_COLOR);
	CURSOR_GOTOXY(1, 1);
	for (int i = 0; i < _rows + 2 + _seps.size(); ++i)
		drawVLine(i + 1);

	for (int i = 0; i < _cols; ++i)
		drawHLine(i + 1);

	for (int i = 0; i < _seps.size(); ++i)
		drawSeparator(_seps[i]);
	setColor(COLOR_BLACK, COLOR_DEFAULT);
}

void Table::drawText(std::string text, int row, int col)
{
	CURSOR_GOTOXY((col - 1) * _spacing + 2, row + 1);
	std::cout << text;
}

void Table::addSeparator(int row)
{
	if (row <= 1)
		return;
	if (row >= _rows)
		return;
	for (int i = 0; i < _seps.size(); ++i)
	{
		if (row == _seps[i])
			return;
	}

	_seps.push_back(row);
}

void Table::drawVLine(int row)
{
	char leftChar = getCorner(5);
	char rightChar = getCorner(5);
	char midChar = ' ';

	if (row == 1)
	{
		leftChar = getCorner(0);
		rightChar = getCorner(1);
		midChar = getCorner(4);
	}
	else if (row == _rows + 2 + _seps.size())
	{
		leftChar = getCorner(3);
		rightChar = getCorner(2);
		midChar = getCorner(4);
	}

	std::cout << leftChar;
	for (int i = 0; i < _width; ++i)
		std::cout << midChar;
	std::cout << rightChar;
}

void Table::drawHLine(int col)
{
	char topChar = getCorner(7);
	char botChar = getCorner(6);
	char midChar = getCorner(5);
	CURSOR_GOTOXY(col * _spacing, 1);
	std::cout << topChar;
	for (int i = 0; i < _rows + _seps.size(); ++i)
	{
		CURSOR_GOTOXY(col * _spacing, i + 2);
		std::cout << midChar;
	}
	CURSOR_GOTOXY(col * _spacing, _rows + _seps.size() + 2);
	std::cout << botChar;
}

void Table::drawSeparator(int row)
{
	CURSOR_GOTOXY(1, row * 2 - 1);
	std::cout << getCorner(8);
	for (int i = 0; i < _width; ++i)
	{
		if (((i + 2) % _spacing) == 0)
			std::cout << getCorner(10);
		else
			std::cout << getCorner(4);
	}
	std::cout << getCorner(9);
}

char Table::getCorner(int index)
{
	switch (index)
	{
		case 0: return char(201); break; //╔
		case 1: return char(187); break; //╗
		case 2: return char(188); break; //╝
		case 3: return char(200); break; //╚
		case 4: return char(205); break; //═
		case 5: return char(186); break; //║
		case 6: return char(202); break; //╩
		case 7: return char(203); break; //╦
		case 8: return char(204); break; //╠
		case 9: return char(185); break; //╣
		case 10: return char(206); break;
	}
	return 0;
}