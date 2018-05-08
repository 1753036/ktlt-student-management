#include "csvloader.h"

CsvLoader::CsvLoader(std::string fileName) 
{
	load(fileName);
}

CsvLoader::~CsvLoader() 
{
	for (unsigned i = 0; i < _data.size(); ++i)
	{
		for (unsigned j = 0; j < _data[i].size(); ++j)
			_data[i][j].clear();
		_data[i].clear();
	}
	_data.clear();
}

bool CsvLoader::load(std::string fileName)
{
	std::ifstream stream(fileName);
	if (stream.is_open() == false)
	{
		std::cout << "File not found: " << fileName << std::endl;
		return false;
	}

	std::string buffer = "";
	while (std::getline(stream, buffer))
	{
		auto vec = parseBuffer(buffer);
		_data.push_back(vec);
	}
	stream.close();
	return true;
}

void CsvLoader::save(std::string fileName)
{
	std::ofstream stream(fileName);

	for (unsigned int i = 0; i < _data.size(); ++i)
	{
		for (unsigned j = 0; j < _data[i].size(); ++j)
		{
			if ((j + 1) == _data[i].size())
				stream << _data[i][j] << std::endl;
			else
				stream << _data[i][j] << ',';
		}
	}

	stream.close();
}

c_vecstr2d CsvLoader::getData()
{
	return _data;
}

int CsvLoader::countDelim(std::string buffer)
{
	int count = 0;

	for (int i = 0; i < buffer.length(); ++i)
		if (buffer[i] == ',')
			++count;

	return count;
}

c_vecstr CsvLoader::parseBuffer(std::string buffer)
{
	c_vecstr res;
	std::stringstream stream(buffer);

	int size = countDelim(buffer) + 1;

	for (int i = 0; i < size; ++i)
	{
		std::getline(stream, buffer, ',');
		res.push_back(buffer);
	}

	stream.clear();
	return res;
}