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

int PmergeMe::binarySearch(const std::vector<int>& a, int item, int maxIndex) {
    int low = 0;
    int high = maxIndex;
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

void PmergeMe::mergePairs(std::vector<int> &a, std::vector<int> &b, std::vector<int> &a1, std::vector<int> &b1)
{
	std::vector<int> jacobsthal = jacobsthalGenerator(a1.size());
	int pos;
	for (size_t i = 0; i < a1.size(); i++)
	{
		pos = binarySearch(a, a1.at(jacobsthal.at(i) - 1), a.size() - 1);
		a.insert(a.begin() + pos, a1.at(jacobsthal.at(i) - 1));
		b.insert(b.begin() + pos, b1.at(jacobsthal.at(i) - 1));
	}
}

void PmergeMe::divideAndSortPairs(std::vector<int> &a, std::vector<int> &b, std::vector<int> &a1, std::vector<int> &b1)
{
	std::vector<int> new_a, new_b; // Temporary vectors to store a & b;

    for (size_t i = 0; i + 1 < a.size(); i += 2)
	{
        if (a[i] < a[i + 1])
		{
            a1.push_back(a[i]);
            b1.push_back(b[i]);
            new_a.push_back(a[i + 1]);
            new_b.push_back(b[i + 1]);
        }
		else
		{
            a1.push_back(a[i + 1]);
            b1.push_back(b[i + 1]);
            new_a.push_back(a[i]);
            new_b.push_back(b[i]);
        }
    }
    a = new_a; // here we update the values of a & b with what we stored in new_a & new_b
    b = new_b;
};

void PmergeMe::mergeInsertionSort(std::vector<int>& a, std::vector<int>& b) {
	std::vector<int> a1;
	std::vector<int> b1;
	int odd_a = -1;
	int odd_b = -1;

	if (a.size() % 2 != 0){
		odd_a = a.at(a.size() - 1);
		a.erase(a.begin() + a.size() - 1);
		odd_b = b.at(b.size() - 1);
		b.erase(b.begin() + b.size() - 1);
	}
	divideAndSortPairs(a, b, a1, b1);
	if (a.size() > 2)
		mergeInsertionSort(a, b);
	mergePairs(a, b, a1, b1);
	if (odd_a != -1) {
		int pos = binarySearch(a, odd_a, a.size() - 1);
		a.insert(a.begin() + pos, odd_a);
		b.insert(b.begin() + pos, odd_b);
	}
}

void PmergeMe::sort_v(size_t size, char** arg)
{	std::vector<int> numbers;
	std::vector<int> a;
	std::vector<int> b;
	int odd = -1;

	for (size_t i = 0; i < size; i++)
		numbers.push_back(parse_args(arg[i]));
	std::cout << "Before: ";
	for (size_t i = 0; i < numbers.size(); i++)
	{
		std::cout << numbers.at(i);
		if (i + 1 != numbers.size())
			std::cout << " ";
		else 
			std::cout << std::endl;
	}
	std::clock_t start = std::clock();
	if (numbers.size() % 2 != 0) {
		odd = numbers.at(numbers.size() - 1);
		numbers.erase(numbers.begin() + numbers.size() - 1);
	}
	
	for (size_t i = 0; i + 1 < numbers.size(); i += 2)
	{
        if (numbers[i] < numbers[i + 1])
		{
            a.push_back(numbers[i + 1]);
            b.push_back(numbers[i]);
        }
		else
		{
            a.push_back(numbers[i]);
            b.push_back(numbers[i + 1]);
        }
	}
	mergeInsertionSort(a, b);
	std::vector<int> jacobsthal;
	int pos;
	jacobsthal = jacobsthalGenerator(b.size());
	for (size_t i = 0; i < b.size(); i++) {
		pos = binarySearch(a, b.at(jacobsthal.at(i) - 1), a.size() - 1);
		a.insert(a.begin() + pos, b.at(jacobsthal.at(i) - 1));
	}	
	if (odd != -1) 
		a.insert(a.begin() + binarySearch(a, odd, a.size() - 1), odd);
	std::clock_t end = std::clock();
	std::cout << "After: ";
	for (size_t i = 0; i < a.size(); i++)
	{
		std::cout << a.at(i);
		if (i + 1 != a.size())
			std::cout << " ";
		else 
			std::cout << std::endl;
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