/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:50:21 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/15 20:58:59 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char **argv)
{
	if(argc != 2) {
		std::cout << "Invalid input, 1 argument needed" << std::endl;
		return 1; 
	}
	try {
		RPN::calculate(argv[1]);
	}
	catch(const std::logic_error& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
	catch(const std::runtime_error& e) {
		std::cout << e.what() << '\n';
		return 1;
	}
	return 0;
}