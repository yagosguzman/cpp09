/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeList.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:34:31 by ysanchez          #+#    #+#             */
/*   Updated: 2025/01/22 21:42:16 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::list<int> PmergeMe::jacobsthalGeneratorList(int size) {
	std::list<int> series;
    int prev = 0;
	int curr = 1;
    while (curr <= size)
	{
        for (int i = curr; i > prev; --i)
            series.push_back(i);
        int next = curr + 2 * prev;
        prev = curr;
        curr = next;
    }
    if (prev < size) // In case size is not a Jacobsthal number we'll add from size to prev + 1 in the vector
        for (int i = size; i > prev; --i)
            series.push_back(i);
    return series;
}

std::list<int>::iterator PmergeMe::binarySearchList(std::list<int>& a, int item) {
    std::list<int>::iterator low = a.begin();
    std::list<int>::iterator mid = a.begin();
    int lowIndex = 0; // Contador para la posición del iterador en 'low'
    int highIndex = std::distance(a.begin(), a.end()); // Número de elementos en la lista

    while (lowIndex < highIndex) {
        int midIndex = lowIndex + (highIndex - lowIndex) / 2;

        // Avanzar 'mid' al punto medio
        mid = a.begin();
        std::advance(mid, midIndex);

        if (item < *mid) {
            highIndex = midIndex; // Reducir el rango superior
        } else {
            lowIndex = midIndex + 1; // Reducir el rango inferior
            low = ++mid; // Mover el iterador 'low' también
        }
    }
    // 'low' será el iterador donde se debe insertar el elemento
    return low;
}

void PmergeMe::printList(std::list<int> &list, int mode)
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

void PmergeMe::mergePairsList(std::list<int>& a, std::list<int>& b) {
    std::list<int> jacobsthal = jacobsthalGeneratorList(b.size());

    std::list<int>::iterator bIt;
    std::list<int>::iterator jacobIt = jacobsthal.begin();

    while (jacobIt != jacobsthal.end()) {
        int index = *jacobIt - 1;
        bIt = b.begin();
        std::advance(bIt, index);
        a.insert(binarySearchList(a, *bIt), *bIt);
        ++jacobIt;
    }
}

void PmergeMe::divideSortList(std::list<int> &a, std::list<int> &b)
{
	std::list<int> new_a;
	for (std::list<int>::iterator it = a.begin(); it != a.end(); it++)
	{
		std::list<int>::iterator next = it;
		++next;
		if (*it < *next)
		{
			b.push_back(*it);
			new_a.push_back(*next);
		}
		else
		{
			b.push_back(*next);
			new_a.push_back(*it);
		}
		it = next;
	}
	a = new_a;
}


void PmergeMe::mergeInsertionList(std::list<int> &a)
{
	std::list<int> b;
	int odd = -1;

	if (a.size() % 2 != 0)
	{
		std::list<int>::iterator it = a.end();
		--it;
		odd = *it;
		a.erase(it); 
	}
	divideSortList(a, b);
	if (a.size() > 2)
		mergeInsertionList(a);
	else if (a.size() == 2 && *a.begin() > *a.rbegin())
		std::swap(*a.begin(), *a.rbegin());
	mergePairsList(a, b);
	if (odd != -1)
		a.insert(binarySearchList(a, odd), odd);
		
}

void PmergeMe::sort_l(size_t size, char** arg) // Para mover elementos de una lista a otra podemos usar la funcion splice
{
	std::list<int> numbers;
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
	if (numbers.size() > 2)
		mergeInsertionList(numbers);
	else if (numbers.size() == 2 && *numbers.begin() > *numbers.rbegin())
		std::swap(*numbers.begin(), *numbers.rbegin());
	if (odd != -1)
		numbers.insert(binarySearchList(numbers, odd), odd);
	std::clock_t end = std::clock();
	printList(numbers, 1);
	for(std::list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
	{
		std::list<int>::iterator next = it;
		++next;
		if (next != numbers.end())
			if (*it > *next)
				std::cout << "Error at " << *it << std::endl;
	}
	double elapsed_microseconds = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
	std::cout << "Time to process a range of " << numbers.size() << " elements with std::list : " << elapsed_microseconds << " us" << std::endl;
}