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


static void divideAndSortPairs(const size_t& size, int numbers[], std::vector<int> a, std::vector<int> b) {
	for (size_t i = 0; i < size - 1; i += 2) {
		if (numbers[i] > numbers[i + 1]){
			a.push_back(numbers[i + 1]);
			b.push_back(numbers[i]);
		}
		else { 
			a.push_back(numbers[i]);
			b.push_back(numbers[i + 1]);
		}
	}
};


void PmergeMe::sort(size_t size, char** arg)
{	int numbers[size];
	std::vector<int> a;
	std::vector<int> b;
	for (size_t i = 0; i < size; i++)
		numbers[i] = parse_args(arg[i]);
	int odd;
	if (size % 2 != 0)
		odd = numbers[size - 1];
	divideAndSortPairs(size, numbers, a ,b);
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