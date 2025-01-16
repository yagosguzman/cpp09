#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};
PmergeMe::PmergeMe(const PmergeMe& copy) {
	*this = copy;
};
PmergeMe& PmergeMe::operator=(const PmergeMe& src) {
	return *this;
};
PmergeMe::~PmergeMe(){};

static int *divideAndSortPairs(const int& size, int numbers[]) {
	int sortedPairs[size];

	for (size_t i = 0; i < size - 1; i += 2) {
		if (numbers[i] > numbers[i + 1]){
			sortedPairs[i] = numbers[i + 1];
			sortedPairs[i + 1] = numbers[i];
		}
		else { 
			sortedPairs[i] = numbers[i];
			sortedPairs[i + 1] = numbers[i + 1];
		}
	}
	return (sortedPairs);
};


int *sort(int size, int numbers[]) {
	int odd;
	if (size % 2 != 0)
		odd = numbers[size - 1];
	numbers = divideAndSortPairs(size, numbers);
	
}