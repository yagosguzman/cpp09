#include "PmergeMe.hpp"

int main (int argc, char **argv){
	if (argc < 2) {
		std::cout << "No arguments find" << std::endl;
		return 1;
	}

	std::vector<int> sortedNumbers;
	try
	{
		PmergeMe::sort_v(static_cast<size_t>(argc - 1), &argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;	
}