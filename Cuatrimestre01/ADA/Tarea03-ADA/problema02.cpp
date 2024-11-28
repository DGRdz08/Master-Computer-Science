#include <iostream>
#include <cstdlib> // For atoi()

// Recursive function to calculate a^b
int potencia(int a, int b) {

    if (b == 0)  return 1;   // Caso base: a^0 = 1

    return a * potencia(a, b - 1);     // Caso recursivo: a^b = a * a^(b-1)
}

int main(int argc, char* argv[]) {
    if (argc != 3) std::cerr <<"Agrega dos argumentos para a y b"<< std::endl;

    int a = std::atoi(argv[1]);
    int b = std::atoi(argv[2]);

    int result = potencia(a, b);

    std::cout << a << "^" << b << " = " << result << std::endl;

    return 0;
}