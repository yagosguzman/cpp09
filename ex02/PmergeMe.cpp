#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {};
PmergeMe::PmergeMe(const PmergeMe& copy) {
	*this = copy;
};
PmergeMe& PmergeMe::operator=(const PmergeMe& src) {
	(void)src;
	return *this;
};
PmergeMe::~PmergeMe(){};

void PmergeMe::mergePairs(std::vector<int> a, std::vector<int> b) {

}

void PmergeMe::divideAndSortPairs(std::vector<int> a, std::vector<int> b) {
	for (size_t i = 0; i < a.size() - 1; i += 2) {
		if (a[i] > a[i + 1]) {
			b.push_back(a[i]);
			a.erase(a.begin() + i);
		}
		else { 
			b.push_back(a[i + 1]);
			a.erase(a.begin() + i + 1);
		}
	}
};

void PmergeMe::mergeInsertionSort(std::vector<int> a) {
	int odd;
	std::vector<int> b;
	if (a.size() % 2 != 0) {
		odd = a.at(a.size() - 1);
		a.pop_back();
	}
	divideAndSortPairs(a ,b);
	if (a.size() > 2)
		mergeInsertionSort(a);
	mergePairs(a, b);
	
}

std::vector<int> PmergeMe::sort(size_t size, char** arg)
{	std::vector<int> a;
	for (size_t i = 0; i < size; i++)
		a.push_back(parse_args(arg[i]));
	mergeInsertionSort(a);
	return (a);	
};

int PmergeMe::parse_args(const std::string& arg)
{
	if (arg.empty())
		throw std::logic_error ("Error: empty argument found");
	size_t i = 0;
	if (arg.at(0) == '+' && arg.size() > 1)
		i = 1;
	if (arg.at(0) == '-')
		throw std::logic_error ("Error: negative numbers not allowed");
	if (arg.size() > 11) // pongo 11 porque pueden ponernos +MAX_INT
		throw std::logic_error ("Error: too large a number");
	while (i < arg.size())
	{
		if (!std::isdigit(arg.at(i++)))
			throw std::logic_error ("Error: invalid argument");
	}
	double value = std::strtod(arg.c_str(), NULL);
	if (value > 2147483647)
		throw std::logic_error ("Error: too large a number");
	return static_cast<int>(value);
};