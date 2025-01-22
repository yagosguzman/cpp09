#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{};

PmergeMe::PmergeMe(const PmergeMe& copy)
{
	*this = copy;
};

PmergeMe& PmergeMe::operator=(const PmergeMe& src)
{
	(void)src;
	return *this;
};

PmergeMe::~PmergeMe()
{};

void PmergeMe::printVector(std::vector<int> &vector, int mode)
{
	if (mode == 0)
		std::cout << "Before: ";
	else if (mode == 1)
		std::cout << "After: ";
	for (size_t i = 0; i < vector.size(); i++)
	{
		std::cout << vector.at(i);
		if (i + 1 != vector.size())
			std::cout << " ";
		else 
			std::cout << "\n"<< std::endl;
	}
}

std::vector<int> PmergeMe::jacobsthalGenerator(int size) {
    std::vector<int> series;
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

int PmergeMe::binarySearch(const std::vector<int>& a, int item) {
    int low = 0;
    int high = a.size() - 1;
	int mid;

    while (low <= high)
	{
        mid = low + ((high - low) / 2);
        if (item < a[mid])
            high = mid - 1; // We move upper range
        else
            low = mid + 1; // We move lower range
    }
    return low; // Once low > high that's our index to put it;
}

void PmergeMe::mergePairs(std::vector<int> &a, std::vector<int> &b)
{
	std::vector<int> jacobsthal = jacobsthalGenerator(b.size());
	for (size_t i = 0; i < b.size(); i++)
		a.insert(a.begin() + binarySearch(a, b.at(jacobsthal.at(i) - 1)), b.at(jacobsthal.at(i) - 1));
}

void PmergeMe::divideAndSortPairs(std::vector<int> &a, std::vector<int> &b)
{
	std::vector<int> new_a;

    for (size_t i = 0; i + 1 < a.size(); i += 2)
	{
        if (a[i] < a[i + 1])
		{
            b.push_back(a[i]);
            new_a.push_back(a[i + 1]);
        }
		else
		{
            b.push_back(a[i + 1]);
            new_a.push_back(a[i]);
        }
    }
    a = new_a;
};

void PmergeMe::mergeInsertionSort(std::vector<int>& a)
{
	std::vector<int> b;
	int odd = -1;

	if (a.size() % 2 != 0) {
		odd = a.at(a.size() - 1);
		a.erase(a.begin() + a.size() - 1);
	}
	divideAndSortPairs(a, b);
	if (a.size() > 2)
		mergeInsertionSort(a);
	else if (a.size() == 2 && a.at(0) > a.at(1))
		std::swap(a[0], a[1]);
	mergePairs(a, b);
	if (odd != -1)
		a.insert(a.begin() + binarySearch(a, odd), odd);
}

void PmergeMe::sort_v(size_t size, char** arg)
{	std::vector<int> numbers;
	int odd = -1;
	for (size_t i = 0; i < size; i++)
		numbers.push_back(parse_args(arg[i]));
	printVector(numbers, 0);
	std::clock_t start = std::clock();
	if (numbers.size() % 2 != 0)
	{
		odd = numbers.at(numbers.size() - 1);
		numbers.erase(numbers.begin() + numbers.size() - 1);
	}
	if (numbers.size() > 2)
		mergeInsertionSort(numbers);
	else if (numbers.size() == 2 && numbers.at(0) > numbers.at(1))
		std::swap(numbers[0], numbers[1]);
	if (odd != -1) 
		numbers.insert(numbers.begin() + binarySearch(numbers, odd), odd);
	std::clock_t end = std::clock();
	printVector(numbers, 1);
	for (size_t i = 1; i < numbers.size(); i++)
	{
		if (numbers.at(i) < numbers.at(i - 1))
			std::cout << "ERROR AT :" << i << std::endl;
	}
	double elapsed_microseconds = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << numbers.size() << " elements with std::vector : " << elapsed_microseconds << " us" << std::endl;
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
	if (arg.size() > 11)
		throw std::logic_error ("Error: too large a number");
	while (i < arg.size())
		if (!std::isdigit(arg.at(i++)))
			throw std::logic_error ("Error: invalid argument");
	double value = std::strtod(arg.c_str(), NULL);
	if (value > 2147483647)
		throw std::logic_error ("Error: too large a number");
	return static_cast<int>(value);
};