/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:10:12 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/16 18:18:08 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::parse_args(const std::string& arg)
{

	for (size_t i = 0; i < arg.size(); i++)
	{
		if ()
	}
	if (arg.at(0) == '-')
		throw std::invalid_argument("Error: negative numbers not allowed");
	if (arg.size() > 10)
		throw std::length_error ("Error: too large a number");
	int value = std::stoi(arg);
	if (value )
}