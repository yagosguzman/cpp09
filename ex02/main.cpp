#include "PmergeMe.hpp"

int main (int argc, char **argv){
	if (argc < 2) {
		std::cout << "No arguments find" << std::endl;
		return 1;
	}
	int arr[argc - 1];

	for (size_t i = 0; i < (argc -1); i++) {
		arr[i] = std::stoi(argv[i + 1]);
	}
	
}