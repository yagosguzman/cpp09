#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <stdlib.h>
#include <climits>
#include <string>
#include <ctime> // Para clock() y CLOCKS_PER_SEC
#include <list>


class PmergeMe
{
private:
	PmergeMe();
	PmergeMe(std::string arg);
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& src);
	~PmergeMe();
	
	static int parse_args(const std::string& arg);
	static std::vector<int> jacobsthalGenerator(int size);
	static void mergeInsertionSort(std::vector<int> &a, std::vector<int> &b);
	static void divideAndSortPairs(std::vector<int> &a, std::vector<int> &b, std::vector<int> &a1, std::vector<int> &b1);
	static void mergePairs(std::vector<int> &a, std::vector<int> &b, std::vector<int> &a1, std::vector<int> &b1);
	static int binarySearch(const std::vector<int>& a, int item, int maxIndex);
	static void printVector(std::vector<int>vector, int mode);

	static void mergeInsertionList(std::list<int> &a, std::list<int> &b);
	static std::list<int> jacobsthalGeneratorList(int size);
	static void printList(std::list<int> list, int mode);

	
	public:
	static void sort_v(size_t size, char** arg);
	static void sort_l(size_t size, char** arg);

};

