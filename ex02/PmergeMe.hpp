#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <stdlib.h>
#include <climits>
#include <string>


class PmergeMe
{
private:
	PmergeMe();
	PmergeMe(std::string arg);
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& src);
	~PmergeMe();
	
	static int parse_args(const std::string& arg);
	
	public:
	static void sort(size_t size, char** arg);

};

