/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:04:33 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/10 21:18:50 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <stdexcept>
#include <fstream>

BitcoinExchange::BitcoinExchange()
{
	_mydata = transferData("data.csv", ',');
}

BitcoinExchange::BitcoinExchange(std::string filename, char separator)
{
	_mydata = transferData(filename, separator);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
{
	_mydata = copy._mydata;
}

BitcoinExchange::~BitcoinExchange()
{

}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& src)
{
	_mydata = src._mydata;
	return (*this);
}

bool BitcoinExchange::validDate(std::string date)
{
	if (date.length() != 10)
		return false;

	for (size_t i = 0; i < date.length(); i++)
	{
		if (i == 4 || i == 7)
			if (date.at(i) != '-')
				return false;
		else
			if (date.at(i) < '0'|| date.at(i) > '9')
				return false;
	}

	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(5, 2));
	int day = std::stoi(date.substr(8, 2));

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
	std::ifstream infile(file);

	if (!infile.is_open())
		throw BitcoinExchange::ErrorFile();
	
	std::string line;
	while (std::getline(infile, line))
	{
		size_t separator_pos = line.find(separator);
		
		if (separator_pos != std::string::npos)
		{
			std::string date = line.substr(0, separator_pos);
			std::string price = line.substr(separator_pos + 1);
			if (validDate(date) && validPrice(price))
			{
				float fprice = std::atof(price.c_str());
				mymap[date] = fprice;
			}
			else
				throw BitcoinExchange::InvalidData();
		}
	}
	infile.close();
	return mymap;
}

const char* BitcoinExchange::ErrorFile::what() const throw()
{
	return "Error trying to open the file";
}

const char* BitcoinExchange::InvalidData::what() const throw()
{
	return "Error: Invalid data";
}