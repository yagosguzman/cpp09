/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:15:29 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/11 21:00:44 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
			throw std::runtime_error("Invalid number of arguments");
		else
		{
			BitcoinExchange test(argv[1], '|');
			test.exchange();
		}
	}
	catch(const std::out_of_range &e)
	{
		std::cout << "Error: " << "Invalidad Data.csv" << '\n';
	}
	catch(const BitcoinExchange::ErrorFile &e)
	{
		std::cout << "Error: imposible open file" << '\n';
	}
	catch(const std::runtime_error &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}