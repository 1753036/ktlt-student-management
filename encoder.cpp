#include "encoder.h"

std::string Encoder::encode(std::string str, std::string password)
{

	int key = makeKey(password);

	for (unsigned i = 0; i < str.length(); ++i)
	{
		str[i] = str.c_str()[i] + key;
	}
	return str;
}

std::string Encoder::decode(std::string str, std::string password)
{
	int key = makeKey(password);
	for (unsigned i = 0; i < str.length(); ++i)
	{
		str[i] = str.c_str()[i] - key;
	}
	return str;
}

int Encoder::makeKey(std::string password)
{
	int key = password.length();
	for (unsigned i = 0; i < password.length(); ++i)
	{
		key = key + password.c_str()[i];
		key = key % 128;
	}
	return key;
}