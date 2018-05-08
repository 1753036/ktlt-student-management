#include "rectangle.h"
#include "misc.h"

#define MAX_CHARACTERS 40

class LEdit
{
public:
	LEdit(std::string title);
	~LEdit();

	void addItem(std::string item);
	void show();

	std::vector<std::string> getVals();
private:

	void refresh();
	void catchKey();

	void printTitle();
	void printItems();
	void printItem(int);

	void moveTo(int ind);

	void updateWidth(std::string text);

	std::string					_title;
	std::vector<std::string>	_items;
	std::vector<std::string>	_itemVals;
	unsigned					_lineWidth;
	int							_currentLine;
};