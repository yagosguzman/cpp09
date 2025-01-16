#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <stdexcept>

class PmergeMe
{
private:
	
public:
	PmergeMe();
	PmergeMe(std::string arg);
	PmergeMe(const PmergeMe& copy);
	~PmergeMe();
	PmergeMe& operator=(const PmergeMe& src);

	int parse_args(const std::string& arg);
};

#endif