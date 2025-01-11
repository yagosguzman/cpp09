#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

class BitcoinExchange
{
private:
	std::map<std::string, float> _mydata;
	std::map<std::string, float> _input;
public:
	BitcoinExchange();
	BitcoinExchange(std::string filename, char separator);
	BitcoinExchange(const BitcoinExchange& copy);
	~BitcoinExchange();

	BitcoinExchange& operator=(const BitcoinExchange& src);

	bool validDate(std::string date);
	bool validPrice(std::string price);
	std::map<std::string, float> transferData(const std::string& file, char separator);
	std::map<std::string, float> transferInput(const std::string& file, char separator);
	float getPrice(std::string inputDate);
	void exchange(void);
	
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