/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:10:12 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/16 18:37:58 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int PmergeMe::parse_args(const std::string& arg)
{
	if (arg.empty())
		throw std::logic_error ("Error: empty argument found");
	size_t i = 0;
	if (arg.at(0) == '+')
		i = 1;
	if (arg.at(0) == '-')
		throw std::logic_error ("Error: negative numbers not allowed");
	if (arg.size() > 11) // pongo 11 porque pueden ponernos +MAX_INT
		throw std::logic_error ("Error: too large a number");
	for (i; i < arg.size(); i++)
	{
		if (!std::isdigit(arg.at(i)))
			throw std::logic_error ("Error: invalid argument");
	}
	long value = std::stol(arg);
	if (value > INT32_MAX)
		throw std::logic_error ("Error: too large a number");
	return static_cast<int>(value);
}