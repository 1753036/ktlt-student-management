#include "misc.h"

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getConsoleSize(int &rows, int &cols)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	cols = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void setFgColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void setBgColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void setColor(WORD bgColor, WORD fgColor)
{
	setBgColor(bgColor);
	setFgColor(fgColor);
}

std::string getPassword(std::string text, int y, bool useFake)
{
	HANDLE screen = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;
	KEY_EVENT_RECORD key;
	DWORD num = 0;

	SetConsoleMode(screen, ENABLE_WINDOW_INPUT);

	std::string password = "";
	std::string fakepass = "";
	CURSOR_GOTOXY(3, y);
	std::cout << text;
	while (1)
	{
		ReadConsoleInput(screen, &event, 1, &num);

		key = event.Event.KeyEvent;

		if (!key.bKeyDown) continue;


		if (key.wVirtualKeyCode <= 90 && key.wVirtualKeyCode >= 65)
		{
			if (password.length() > 24)
				continue;

			password += char(key.wVirtualKeyCode + ('a' - 'A'));
			if (useFake)
				fakepass += '*';
		}
			
		else if (key.wVirtualKeyCode >= 48 && key.wVirtualKeyCode <= 57 || key.wVirtualKeyCode == VK_SPACE)
		{
			if (password.length() > 24)
				continue;

			password += char(key.wVirtualKeyCode);
			if (useFake)
				fakepass += '*';
		}
		else if (key.wVirtualKeyCode == VK_BACK)
		{
			if (password.length() > 0)
			{
				CURSOR_GOTOXY(text.length() + password.length() + 2, y);
				std::cout << ' ';
				password.pop_back();
				if (useFake)
					fakepass.pop_back();
			} else 
			{
				CURSOR_GOTOXY(text.length() + 3, y);
			}
		}
		else if (key.wVirtualKeyCode == 13)
			return password;

		if (password.length() > 0)
		{
			CURSOR_GOTOXY(text.length() + password.length() + 2, y);
			if (useFake)
				std::cout << '*';
			else
				std::cout << password[password.length() - 1];
		}

		FlushConsoleInputBuffer(screen);
	}
	return "";
}

void loginField(std::string &username, std::string &password)
{
	CLEAR_CMD();
	Rectangle::draw(24, 5);
	CURSOR_GOTOXY(3, 3);
	std::cout << "Password: ";
	username = getPassword("Username: ", 2, false);
	password = getPassword("Password: ", 3, true);
}

void changePassField(std::string &username, std::string &password, std::string &newPassword)
{
	CLEAR_CMD();
	Rectangle::draw(24, 6);
	CURSOR_GOTOXY(3, 3);
	std::cout << "Old Password: ";
	CURSOR_GOTOXY(3, 4);
	std::cout << "New Password: ";
	username    = getPassword("Username: ", 2, false);
	password    = getPassword("Old Password: ", 3, true);
	newPassword = getPassword("New Password: ", 4, true);
}

void strToUpper(std::string &str)
{
	for (unsigned i = 0; i < str.length(); ++i)
		str[i] = (str[i] >= 'a' && str[i] <= 'z') ? str[i] - ('a' - 'A') : str[i];

}

void showStatus(std::string status, int x, int y, int w, int h)
{
	CURSOR_GOTOXY(x, y);
	Rectangle::draw(w, h);

	CURSOR_GOTOXY(x + 3, y + 1);
	std::cout << status;
}

std::string intToDay(int i)
{
	switch (i)
	{
	case 0: return "Monday";
	case 1: return "Tuesday";
	case 2: return "Wednesday";
	case 3: return "Thursday";
	case 4: return "Friday";
	case 5: return "Saturday";
	case 6: return "Sunday";
	}
}