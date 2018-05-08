#ifndef ENCODER_H
#define ENCODER_H

#include <iostream>
#include <string>

class Encoder
{
	public:
		static std::string encode(std::string, std::string);
		static std::string decode(std::string, std::string);
	private:
		static int makeKey(std::string);
};

#endif // ENCODER_H
