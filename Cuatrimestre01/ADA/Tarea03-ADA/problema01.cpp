#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

 
int recursiveSum(const std::vector<int>& vec, int n) {
    if (n == 1) return vec[0]; // Caso base : 1 elemento
    return vec[n - 1] + recursiveSum(vec, n - 1); // Caso recursivo : n elementos 
}


float recursiveAverage(const std::vector<int>& vec, int n) {
    int sum = recursiveSum(vec, n);
    return static_cast<float>(sum) / n;  
}

int main(int argc, char* argv[]) {
    if (argc != 2) std::cerr << "Agrega un argumento para el archivo" << std::endl;

    std::ifstream file(argv[1]);
    if (!file)  std::cerr << "Error al abrir el archivo" << std::endl;

    int n;
    std::vector<int> numbers;

    file >> n;
    std::string line;
    std::getline(file, line);  
    std::getline(file, line);  

    std::istringstream iss(line);
    int num;
    while (iss >> num)  numbers.push_back(num);

    if (numbers.size() != n)    std::cerr << "La cantidad de números no coincide con el tamaño del vector" << std::endl;

    float average = recursiveAverage(numbers, n);
    std::cout << "Promedio: " << average << std::endl;

    return 0;
}