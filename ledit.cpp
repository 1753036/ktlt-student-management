#include "ledit.h"

LEdit::LEdit(std::string title)
{
	_title = title;
	_lineWidth = _title.size();
}

LEdit::~LEdit()
{
	_title.clear();
	for (unsigned i = 0; i < _items.size(); ++i)
		_items[i].clear();

	for (unsigned i = 0; i < _itemVals.size(); ++i)
		_itemVals[i].clear();
	_itemVals.clear();
	_items.clear();
}

void LEdit::show()
{
	refresh();
	printTitle();
	printItems();
	moveTo(0);
	catchKey();
}

void LEdit::refresh()
{
	
	for (unsigned i = 0; i < _itemVals.size(); ++i)
	{
		_itemVals[i].clear();
	}
}

void LEdit::moveTo(int ind)
{
	int x = _items[ind].length() + _itemVals[ind].length() + 5;
	int y = ind + 5;

	_currentLine = ind;

	CURSOR_GOTOXY(x, y);
}

void LEdit::addItem(std::string item)
{
	_items.push_back(item);
	_itemVals.push_back("");
	updateWidth(item);
}

void LEdit::catchKey()
{
	std::cin.ignore();
	for (int i = 0; i < _items.size(); ++i)
	{
		moveTo(i);
		std::getline(std::cin, _itemVals[i]);
	}
}

std::vector<std::string> LEdit::getVals()
{
	return _itemVals;
}

void LEdit::printTitle()
{
	int w = (_lineWidth + MAX_CHARACTERS) / 2;
	int h = 3;
	int x = 1 + w - (_title.length() / 2);
	int y = 2;
	CURSOR_GOTOXY(1, 1);
	Rectangle::draw(w, h);
	CURSOR_GOTOXY(x, y);
	std::cout << _title;
}

void LEdit::printItems()
{
	int w = (_lineWidth + MAX_CHARACTERS) / 2;
	int h = _items.size() + 2;
	int x = 1;
	int y = 4;

	CURSOR_GOTOXY(x, y);
	Rectangle::draw(w, h);

	for (int i = 0; i < _items.size(); ++i)
		printItem(i);
	
}

void LEdit::printItem(int ind)
{
	int x = 3;
	int y = ind + 5;
	CURSOR_GOTOXY(x, y);
	std::cout << _items[ind] << ": ";
}

void LEdit::updateWidth(std::string text)
{
	if (_lineWidth < text.size())
		_lineWidth = text.size();
}