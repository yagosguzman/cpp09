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

// Función que genera la serie de grupos de Jacobsthal ajustada al tamaño
std::vector<int> PmergeMe::generateJacobsthalSeriesAdjusted(int size) {
    std::vector<int> series;
    // Generar los números de Jacobsthal directamente
    int prev = 0, curr = 1;
    while (curr <= size) {
        // Agregar el grupo definido por [prev+1, curr] en orden inverso
        for (int i = curr; i > prev; --i) {
            series.push_back(i);
        }
        // Calcular el siguiente número de Jacobsthal
        int next = curr + 2 * prev;
        prev = curr;
        curr = next;
    }
    // Si el tamaño no cuadra con un número de Jacobsthal
    if (prev < size) {
        // Agregar los índices restantes desde `size` hacia `prev+1`
        for (int i = size; i > prev; --i) {
            series.push_back(i);
        }
    }
    return series;
}

int PmergeMe::binarySearchLimited(const std::vector<int>& a, int item, int maxIndex) {
    int low = 0;
    int high = maxIndex; // Ajustamos 'high' para que sea inclusivo
	int mid;

    while (low <= high) {
        mid = low + ((high - low) / 2);

        if (item < a[mid]) {
            high = mid - 1; // Mover el rango superior
        } else {
            low = mid + 1; // Mover el rango inferior
        }
    }

    return low; // Retornar la posición de inserción
}

void PmergeMe::mergePairs(std::vector<int> &a, std::vector<int> &b, std::vector<int> &a1, std::vector<int> &b1) {
	std::vector<int> jacobsthal;

	int pos;
	jacobsthal = generateJacobsthalSeriesAdjusted(a1.size());
	for (size_t i = 0; i < a1.size(); i++) {
		pos = binarySearchLimited(a, a1.at(jacobsthal.at(i) - 1), a.size() - 1);
		a.insert(a.begin() + pos, a1.at(jacobsthal.at(i) - 1));
		b.insert(b.begin() + pos, b1.at(jacobsthal.at(i) - 1));
	}
	
}

void PmergeMe::divideAndSortPairs(std::vector<int> &a, std::vector<int> &b, std::vector<int> &a1, std::vector<int> &b1) {
	 std::vector<int> new_a, new_b; // Vectores temporales para almacenar los valores restantes

    // Iterar sobre los pares en a y b
    for (size_t i = 0; i + 1 < a.size(); i += 2) {
        // Comparar los elementos del par
        if (a[i] < a[i + 1]) {
            a1.push_back(a[i]);         // Menor valor a a1
            b1.push_back(b[i]);         // Menor valor a b1
            new_a.push_back(a[i + 1]);  // Mayor valor a new_a
            new_b.push_back(b[i + 1]);  // Mayor valor a new_b
        } else {
            a1.push_back(a[i + 1]);     // Menor valor a a1
            b1.push_back(b[i + 1]);     // Menor valor a b1
            new_a.push_back(a[i]);      // Mayor valor a new_a
            new_b.push_back(b[i]);      // Mayor valor a new_b
        }
    }

    // Actualizar los vectores originales
    a = new_a;
    b = new_b;
};

void PmergeMe::mergeInsertionSort(std::vector<int>& a, std::vector<int>& b) {
	std::vector<int> a1;
	std::vector<int> b1;
	int odd_a = -1;
	int odd_b = -1;
	int pos;

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
		pos = binarySearchLimited(a, odd_a, a.size() - 1);
		a.insert(a.begin() + pos, odd_a);
		b.insert(b.begin() + pos, odd_b);
	}
}

std::vector<int> PmergeMe::sort(size_t size, char** arg)
{	std::vector<int> numbers;
	std::vector<int> a;
	std::vector<int> b;
	
	int odd = -1;
	for (size_t i = 0; i < size; i++)
		numbers.push_back(parse_args(arg[i]));
	std::clock_t start = std::clock();
	if (numbers.size() % 2 != 0) {
		odd = numbers.at(numbers.size() - 1);
		numbers.erase(numbers.begin() + numbers.size() - 1);
	}
	
	for (size_t i = 0; i + 1 < numbers.size(); i += 2) {
        // Comparar los elementos del par
        if (numbers[i] < numbers[i + 1]) {
            a.push_back(numbers[i + 1]);         // Menor valor a a1
            b.push_back(numbers[i]);         // Menor valor a b1
        } else {
            a.push_back(numbers[i]);         // Menor valor a a1
            b.push_back(numbers[i + 1]);       // Menor valor a b1
        }
}
	mergeInsertionSort(a, b);
	std::vector<int> jacobsthal;


	int pos;
	jacobsthal = generateJacobsthalSeriesAdjusted(b.size());
	for (size_t i = 0; i < b.size(); i++) {
		pos = binarySearchLimited(a, b.at(jacobsthal.at(i) - 1), a.size() - 1);
		a.insert(a.begin() + pos, b.at(jacobsthal.at(i) - 1));
	}




	
	if (odd != -1) 
		a.insert(a.begin() + binarySearchLimited(a, odd, a.size() - 1), odd);
	std::clock_t end = std::clock();
	double elapsed_microseconds = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;

    // Imprime el tiempo transcurrido
    std::cout << "Tiempo de ejecución: " << elapsed_microseconds << " us" << std::endl;
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