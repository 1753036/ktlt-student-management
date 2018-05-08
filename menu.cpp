#include "menu.h"

std::string Menu::_trigData = "";
std::string Menu::_trigTit = "";
Menu		*Menu::_trigMenu = NULL;

Menu::Menu(std::string title)
{
	_title = title;
	_menuWidth = _title.length() + 1;
	_lastChoice = 0;
}

Menu::~Menu()
{
//	std::cout << this << std::endl;

	for (unsigned i = 0; i < _vMenuItem.size(); ++i)
	{
		if (_vMenuItem[i].subMenu != NULL)
			delete (Menu*)_vMenuItem[i].subMenu;

		_vMenuItem[i].text.clear();
	}

	_title.clear();
	_vMenuItem.clear();
}

void Menu::clear()
{
	for (unsigned i = 0; i < _vMenuItem.size(); ++i)
	{
		if (_vMenuItem[i].subMenu != NULL)
			delete (Menu*)_vMenuItem[i].subMenu;

		_vMenuItem[i].text.clear();
	}

	_vMenuItem.clear();
	_backMenuItem = NULL;
	_lastChoice = 0;
}

std::string Menu::getTrigItem()
{
	return Menu::_trigData;
}

std::string Menu::getTrigTit()
{
	return Menu::_trigTit;
}


Menu *Menu::getTrigMenu()
{
	return Menu::_trigMenu;
}

int Menu::addItem(std::string text, void (*func)())
{
	updateMenuWidth(text);
	_vMenuItem.push_back({text, func, MenuTypeItem, NULL});
	return _vMenuItem.size() - 1;
}

Menu* Menu::addSubMenu(std::string text, std::string title)
{
	updateMenuWidth(text);

	Menu* tmp = new Menu(title);
	tmp->_backMenuItem = this;

	_vMenuItem.push_back({text, NULL, MenuTypeSubMenu, tmp});

	return tmp;
}

void Menu::addBack(Menu *par)
{
	_backMenuItem = par;
}

void Menu::show()
{
	CLEAR_CMD();

	printTitle();
	printMenu();

	getChoice();
}

void Menu::update()
{

}

void Menu::choiceUp(unsigned &choice)
{
	if (choice == _vMenuItem.size())
	{
		if (_backMenuItem == NULL)
			return;

		--choice;
		printBackMenuItem(false);
		printMenuItem(choice, true);
		return;
	}

	if (choice <= 0)
		return;

	printMenuItem(choice, false);
	printMenuItem(choice - 1, true);
	--choice;
}

void Menu::choiceDown(unsigned &choice)
{
	if (choice + 1 >= _vMenuItem.size())
	{
		if (choice == _vMenuItem.size() || _backMenuItem == NULL)
			return;
			
		printMenuItem(choice, false);
		printBackMenuItem(true); 
		++choice;
		return;
	}

	printMenuItem(choice, false);
	printMenuItem(choice + 1, true);
	++choice;
}


void Menu::getChoice()
{
	HANDLE screen = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;
	KEY_EVENT_RECORD key;
	DWORD num = 0;

	SetConsoleMode(screen, ENABLE_WINDOW_INPUT);

	unsigned choice = _lastChoice;
	bool running = true;

	while (running)
	{
		ReadConsoleInput(screen, &event, 1, &num);

		key = event.Event.KeyEvent;

		if (!key.bKeyDown) continue;

		switch (key.wVirtualKeyCode)
		{
			case VK_UP: choiceUp(choice); break;
			case VK_DOWN: choiceDown(choice); break;
			case 13: 
				doTheChoice(choice); 
				FlushConsoleInputBuffer(screen);
				running = false;
				break;
		}

		FlushConsoleInputBuffer(screen);
	}

}

void Menu::doTheChoice(unsigned choice)
{
	CLEAR_CMD();
	_lastChoice = choice;
	Menu::_trigMenu = this;
	Menu::_trigTit = _title;
	if (choice == _vMenuItem.size())
	{
		_backMenuItem->show();
		Menu::_trigData = "[Back]";
		return;
	}

	switch (_vMenuItem[choice].type)
	{
		case MenuTypeItem:
			if (_vMenuItem[choice].func != NULL)
			{
				Menu::_trigData = _vMenuItem[choice].text;
				_vMenuItem[choice].func();
			}
			break;
		case MenuTypeSubMenu:
			static_cast<Menu*>(_vMenuItem[choice].subMenu)->show();
			break;
		default: break;
	}
}

void Menu::updateMenuWidth(std::string text)
{
	if (text.length() > _menuWidth)
		_menuWidth = text.length();
}

void Menu::printTitle()
{
	int x = 4 + (_menuWidth / 2) - (_title.length() / 2);
	int y = 1;
	int w = (_menuWidth / 2) + 5;
	int h = 3;
	
	CURSOR_GOTOXY(1, y);
	Rectangle::draw(w, h);
	CURSOR_GOTOXY(x, y + 1);
	setColor(COLOR_BLACK, TITLE_COLOR);
	std::cout << _title;
	setColor(COLOR_BLACK, COLOR_DEFAULT);
}

void Menu::printMenu()
{
	int y = 4;
	int w = (_menuWidth / 2) + 5;
	int h = (_vMenuItem.size()) + ((_backMenuItem) ? 4 : 2);

	CURSOR_GOTOXY(1, y);
	Rectangle::draw(w, h);

	for (unsigned i = 0; i < _vMenuItem.size(); ++i)
		printMenuItem(i, false);

	if (_backMenuItem)
		printBackMenuItem(false);

	if (_lastChoice == _vMenuItem.size())
		printBackMenuItem(true);
	else
		printMenuItem(_lastChoice, true);
	
}

void Menu::printMenuItem(int ind, bool isSelected)
{
	int y = ind + 5;
	int w = (_menuWidth / 2) + 3;
	int h = (_vMenuItem.size()) + ((_backMenuItem) ? 4 : 2);

	if (isSelected)
		setColor(SELECTED_BG, SELECTED_FG);
	else
		setColor(COLOR_BLACK, COLOR_DEFAULT);


	CURSOR_GOTOXY(2, y);
	std::cout << " " << ind + 1 << ((ind < 9) ? ".  " : ". ") << _vMenuItem[ind].text;
}

void Menu::printBackMenuItem(bool isSelected)
{
	int x = 2;
	int y = (_vMenuItem.size()) + 6;
	CURSOR_GOTOXY(x, y);

	if (isSelected)
		setColor(SELECTED_BG, SELECTED_FG);
	else
		setColor(COLOR_BLACK, COLOR_DEFAULT);

	std::cout << " 0.  Back";
}
