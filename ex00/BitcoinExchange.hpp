#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

class BitcoinExchange
{
private:
	std::map<std::string, float> _mydata;
	std::vector<std::string> _inputdate;
	std::vector<std::string> _inputvalue;
public:
	BitcoinExchange();
	BitcoinExchange(std::string file, char *infile);
	BitcoinExchange(const BitcoinExchange& copy);
	~BitcoinExchange();

	BitcoinExchange& operator=(const BitcoinExchange& src);

	bool validDate(std::string date);
	bool validPrice(std::string price);
	std::map<std::string, float> transferData(const std::string& file, char separator);
	void transferInput(char const *infile);
	void convertInput(void);
	float getPrice(std::string inputDate);

	class ErrorFile : public std::exception{
		public:
			virtual const char* what() const throw();
	};

	class InvalidData : public std::exception{
		public:
			virtual const char* what() const throw();
	};
};

#endif