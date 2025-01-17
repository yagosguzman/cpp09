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
	static void mergeInsertionSort(std::vector<int> a);
	static void divideAndSortPairs(std::vector<int> a, std::vector<int> b);
	static void mergePairs(std::vector<int> a, std::vector<int> b);
	
	public:
	static std::vector<int> sort(size_t size, char** arg);

};

