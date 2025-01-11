/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:04:33 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/11 21:11:55 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <exception>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>

BitcoinExchange::BitcoinExchange()
{
	_mydata = transferData("data.csv", ',');
	_input = transferInput("input.txt", '|');
}

BitcoinExchange::BitcoinExchange(std::string filename, char separator)
{
		_mydata = transferData("data.csv", ',');
		_input = transferInput(filename, separator);
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
	if (price.at(0) < '0' || price.at(0) > '9')
		return false;
	for (size_t i = 1; i < price.length(); i++)
	{
		if (price.at(i) == '.')
		{
			dot++;
			if (i == 0 || i == price.length() - 1)
				return false;
		}
		if ((price.at(i) < '0' || price.at(i) > '9') && price.at(i) != '.')
			return false;
	}
	if (dot > 1)
		return false;
	return true;
}

std::map<std::string, float> BitcoinExchange::transferData(const std::string& file, char separator)
{
	std::map<std::string, float> mymap;
	std::ifstream infile(file.c_str());

	if (!infile.is_open())
		throw BitcoinExchange::ErrorFile();
	std::string line;
	std::getline(infile, line);
	while (std::getline(infile, line))
	{
		size_t separator_pos = line.find(separator);
		if (separator_pos != std::string::npos)
		{
			std::string date = line.substr(0, separator_pos);
			std::string price = line.substr(separator_pos + 1);
			if ((validDate(date) && validPrice(price)))
			{
				float fprice = std::atof(price.c_str());
				mymap[date] = fprice;
			}
			else
				throw std::out_of_range("invalid data");
		}
	}
	infile.close();
	return mymap;
}

std::map<std::string, float> BitcoinExchange::transferInput(const std::string& file, char separator)
{
	std::map<std::string, float> mymap;
	std::ifstream infile(file.c_str());

	if (!infile.is_open())
		throw BitcoinExchange::ErrorFile();
	std::string line;
	std::getline(infile, line);
	while (std::getline(infile, line))
	{
		line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
		size_t separator_pos = line.find(separator);
		if (separator_pos != std::string::npos)
		{
			try {
				std::string date = line.substr(0, separator_pos);
				std::string price = line.substr(separator_pos + 1);
				if ((validDate(date) && validPrice(price)))
				{
					float fprice = std::atof(price.c_str());
					mymap[date] = fprice;
				}
			}
			catch(const std::out_of_range &e)
			{}
			// else
			// 	throw BitcoinExchange::InvalidData();
		}
	}
	infile.close();
	return mymap;
}

float BitcoinExchange::getPrice(std::string inputDate)
{
	std::map<std::string, float>::iterator it;
	it = _mydata.lower_bound(inputDate);
	if (it != _mydata.begin() && it->first != inputDate)
		it = --it;
	return it->second;
}	

void BitcoinExchange::exchange(void)
{
	std::map<std::string, float>::iterator it;
	for (it = _input.begin(); it != _input.end(); it++)
	{
		try
		{
			if (!validDate(it->first))
				throw BitcoinExchange::InvalidData();
			if (it->second < 0 || it->second > 1000)
				throw std::logic_error("Error: too large a number");
			std::cout << it->first << " => " << it->second << " = " << getPrice(it->first)*it->second << std::endl;
		}
		catch(std::exception &e)
		{
			std::cout << e.what() << std::endl;
		};
	}
}

const char* BitcoinExchange::ErrorFile::what() const throw()
{
	return "Error trying to open the file";
}

const char* BitcoinExchange::InvalidData::what() const throw()
{
	return "Error: Invalid data";
}