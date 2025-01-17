/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:15:29 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/17 19:05:53 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "Invalid number of arguments" << std::endl;
		return 1;
	}
	try
	{
		BitcoinExchange test;
		test.convertInput(argv[1]);
	}
	catch(const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}