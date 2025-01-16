#include <iostream>
#include <vector>
#include <algorithm>

class PmergeMe
{
private:
	PmergeMe();
	PmergeMe(const PmergeMe& copy);
	PmergeMe& operator=(const PmergeMe& src);
	~PmergeMe();

	
public:
	int *sort(int size, int numbers[]);
};

