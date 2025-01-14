/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:04:33 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/14 19:56:46 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>

BitcoinExchange::BitcoinExchange()
{
	_mydata = transferData("data.csv", ',');
	_input = transferInput("input.txt", '|');
}

BitcoinExchange::BitcoinExchange(std::string file, char *infile)
{
		_mydata = transferData(file, ',');
		_input = transferInput(infile, '|');
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
{
	_mydata = copy._mydata;
	_input = copy._input;
}

BitcoinExchange::~BitcoinExchange()
{}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
	_mydata = src._mydata;
	_input = src._input;
	return (*this);
}

bool BitcoinExchange::validDate(std::string date)
{
	if (date.length() != 10)
		return false;

	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
		{
			if (date.at(i) != '-')
				return false;
		}
		else
			if (date.at(i) < '0'|| date.at(i) > '9')
				return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 0 || month < 1 || month > 12 || day < 1)
		return false;

	int daysPerMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0))
		daysPerMonth[1] = 29;
	
	if (day <= daysPerMonth[month - 1])
		return true;
	else
		return false;
}

bool BitcoinExchange::validPrice(std::string price)
{
	size_t dot = 0;
	size_t i = 0;
	if (price.at(0) == '-' || price.at(0) == '+')
		i++;
	while(i < price.length())
	{
		if ((price.at(i) < '0' || price.at(i) > '9') && price.at(i) != '.')
			return false;
		if (price.at(i) == '.')
		{
			dot++;
			if (i == 0 || i == price.length() - 1)
				return false;
		}
		i++;
	}
	if (dot > 1)
		return false;
	return true;
}

std::map<std::string, float> BitcoinExchange::transferData(const std::string& infile, char separator) // For modularity we put the separator as a variable
{
	std::map<std::string, float> mymap;
	std::ifstream file(infile.c_str());

	if (!file.is_open())
		throw BitcoinExchange::ErrorFile();
	std::string line;
	std::getline(file, line); // To skip the first line where there are no numbers
	while (std::getline(file, line))
	{
		size_t separator_pos = line.find(separator);
		if (separator_pos != std::string::npos) // If it doesn't find the separator, we'll skip the current line and check the next one
		{
			std::string date = line.substr(0, separator_pos);
			std::string price = line.substr(separator_pos + 1);
			if ((validDate(date) && validPrice(price)))
			{
				float fprice = std::atof(price.c_str());
				if (fprice < 0)
					throw InvalidData();
				else
					mymap[date] = fprice;
			}
			else
				throw InvalidData();
		}
	}
	file.close();
	return mymap;
}

std::map<std::string, std::string> BitcoinExchange::transferInput(char const *infile, char separator)
{
	std::map<std::string, std::string> input;
	std::ifstream file(infile);
	if (!file.is_open())
		throw ErrorFile();
	std::string line;
	std::getline(file, line);
	std::string date;
	std::string value;
	while (std::getline(file, line))
	{
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		std::istringstream ss(line);
		std::getline(ss, date, separator);
		std::getline(ss, value, separator);
		input[date] = value;
	}
	return input;
}
	void BitcoinExchange::convertInput(void)
{
	std::map<std::string,std::string>::iterator it;
	for (it = _input.begin(); it != _input.end(); it++)
	{
		if (it->first.empty())
		{
			std::cout << "Error: empty date" << std::endl;
			continue;
		}
		if (it->second.empty())
		{
			std::cout << "Error: empty value" << std::endl;
			continue;
		}
		if (validDate(it->first) == false)
		{
			std::cout << "Error: invalid date => " << it->first << std::endl;
			continue;
		}
		if (validPrice(it->second))
		{
			float value = std::atof(it->second.c_str());
			if (value < 0)
			{
				std::cout << "Error: Not a positive number => " << value << std::endl;
				continue;
			}
				if (value > 1000)
			{
				std::cout << "Error: Too large a number => " << value << std::endl;
				continue;
			}
			std::cout << it->first << " => " << it->second << " = " << (getPrice(it->first) * value) << std::endl;
		}
		else
			std::cout << "Error: invalid value => " << it->second << std::endl; // FALTA DISTINGUIR ENTRE NEGATIVOS Y ELEMENTOS NO VALIDOS
	}
}

float BitcoinExchange::getPrice(std::string inputDate)
{
	std::map<std::string, float>::iterator it;
	it = _mydata.lower_bound(inputDate);
	if (it != _mydata.begin() && it->first != inputDate)
		it = --it;
	return it->second;
}	

const char* BitcoinExchange::ErrorFile::what() const throw()
{
	return "Error trying to open the file";
}

const char* BitcoinExchange::InvalidData::what() const throw()
{
	return "Error: Invalid data";
}