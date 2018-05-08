#ifndef MENU_H
#define MENU_H

#include "misc.h"
#include "rectangle.h"

#define TITLE_COLOR COLOR_GREEN
#define SELECTED_BG COLOR_GRAY
#define SELECTED_FG COLOR_YELLOW

enum MenuType
{
	MenuTypeItem = 0,
	MenuTypeSubMenu = 0x2,
};

struct MenuItem
{
	std::string		text;
	void			(*func)();
	MenuType		type;
	void*			subMenu;
};

class Menu
{
	public:
		Menu(std::string);
		~Menu();

		int			addItem(std::string, void (*)());
		void			addBack(Menu *par);
		Menu*		addSubMenu(std::string, std::string);
		void		show();
		void		update();
		void		clear();

		static std::string  getTrigItem();
		static std::string  getTrigTit();
		static Menu			*getTrigMenu();
	private:
		void		choiceUp(unsigned &);
		void		choiceDown(unsigned &);

		void		getChoice();
		void		doTheChoice(unsigned);

		void		updateMenuWidth(std::string);

		void		printTitle();
		void		printMenu();
		void		printMenuItem(int, bool);
		void		printBackMenuItem(bool);

		std::string					_title;
		std::vector<MenuItem>		_vMenuItem;
		Menu*						_backMenuItem;
		unsigned					_menuWidth;

		unsigned					_lastChoice;

		static std::string			_trigData;
		static std::string			_trigTit;
		static Menu					*_trigMenu;

};

#endif // MENU_H
