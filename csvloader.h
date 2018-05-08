#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

typedef std::vector<std::string> c_vecstr;
typedef std::vector<c_vecstr>	 c_vecstr2d;

class CsvLoader
{
public:
	CsvLoader(std::string fileName);
	~CsvLoader();
	
	bool		load(std::string fileName);
	void		save(std::string fileName);

	c_vecstr2d	getData();
private:
	c_vecstr2d	_data;

	int			countDelim(std::string str);
	c_vecstr	parseBuffer(std::string buffer);
};