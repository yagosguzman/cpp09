/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeList.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:34:31 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/22 18:20:38 by ysanchez         ###   ########.fr       */
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

void PmergeMe::mergeInsertionList(std::list<int> &a, std::list<int> &b)
{
	std::list<int> a1;
	std::list<int> b1;
	int odd_a = -1;
	int odd_b = -1;

	if (a.size() % 2 != 0)
	{
		std::list<int>::iterator it_a = a.end();
		--it_a;
		odd_a = *it_a;
		a.erase(it_a);
		std::list<int>::iterator it_b = b.end();
		--it_b;
		odd_b = *it_b;
		b.erase(it_b); 
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
	std::clock_t start = std::clock();
	if (numbers.size() % 2 != 0)
	{
		std::list<int>::iterator it = numbers.end();
		--it;
		odd = *it;
		numbers.erase(it); 
	}
	std::list<int>::iterator end = numbers.end();
	end--;
	for (std::list<int>::iterator it = numbers.begin(); it != end; it++)
	{
		std::list<int>::iterator next = it;
		next++;
		if (*it < *next)
		{
			a.push_back(*next);
			b.push_back(*it);
		}
		else
		{
			a.push_back(*it);
			b.push_back(*next);
		}
		it = next;
	}
	mergeInsertionList(a, b);
	std::list<int> jacobsthal;
	int pos;
	jacobsthal = jacobsthalGeneratorList(b.size());
	for (size_t i = 0; i < b.size(); i++)
	{
		pos = binarySearch(a, b.at(jacobsthal.at(i) - 1), a.size() - 1);
		a.insert(a.begin() + pos, b.at(jacobsthal.at(i) - 1));
	}
	if (odd != -1)
		a.insert(a.begin() + pos, b.at(jacobsthal.at(i) - 1));
	std::clock_t end = std::clock();
	printList(a, 1);
	double elapsed_microseconds = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::list : " << elapsed_microseconds << " us" << std::endl;
}