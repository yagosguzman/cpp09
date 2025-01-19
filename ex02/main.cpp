#include "PmergeMe.hpp"

int main (int argc, char **argv){
	if (argc < 2) {
		std::cout << "No arguments find" << std::endl;
		return 1;
	}

	std::vector<int> sortedNumbers;
	try
	{
		sortedNumbers = PmergeMe::sort(static_cast<size_t>(argc - 1), &argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	std::cout << "Sorted numbers:: " << std::endl;
	for (size_t i = 0; i < sortedNumbers.size(); i++) {
		std::cout << sortedNumbers[i] ;
	}
	std::cout << std::endl;
	return 0;	
}