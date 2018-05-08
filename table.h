#pragma once

#include <iostream>

#include "misc.h"

#define TABLE_BORDER_COLOR COLOR_YELLOW
class Table
{
public:
	Table(std::string title, int rows, int cols);
	~Table();

	void show();
	void drawText(std::string text, int row, int col);
	void addSeparator(int row);
private:
	void drawHLine(int row);
	void drawVLine(int col);
	void drawSeparator(int row);
	char getCorner(int index);

	std::string			_title;
	int					_rows;
	int					_cols;
	int					_width;
	int					_height;
	int					_spacing;
	std::vector<int>	_seps;
};