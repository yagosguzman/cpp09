/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeList.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:34:31 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/21 17:51:31 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void PmergeMe::printList(std::list<int> list, int mode)
{
	if (mode == 0)
		std::cout << "Before: ";
	else if (mode == 1)
		std::cout << "After: ";
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++)
	{
		std::cout << *it;
		std::list<int>::iterator next = it;
		if (++next != list.end())
			std::cout << " ";
		else 
			std::cout << std::endl;
	}
}

void PmergeMe::sort_l(size_t size, char** arg) // Para mover elementos de una lista a otra podemos usar la funcion splice
{
	std::list<int> numbers;
	std::list<int> a;
	std::list<int> b;
	int odd = -1;

	for (size_t i = 0; i < size; i++)
		numbers.push_back(parse_args(arg[i]));
	printList(numbers, 0);
	//std::clock_t start = std::clock();
	if (numbers.size() % 2 != 0)
	{
		std::list<int>::iterator it = numbers.end();
		--it;
		odd = *it;
		numbers.erase(it); 
	}
}