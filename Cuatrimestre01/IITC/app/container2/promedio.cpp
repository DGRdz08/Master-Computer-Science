#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>

int main() {
    std::ifstream archivo("/shared_memory/datos.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo\n";
        return 1;
    }

    int n, suma = 0;
    archivo >> n;

    if (n <= 0) {
        std::cerr << "Número inválido de elementos\n";
        return 1;
    }

    std::vector<int> numeros(n);
    for (int i = 0; i < n; i++) {
        archivo >> numeros[i];
        suma += numeros[i];
    }
    archivo.close();

    double promedio = static_cast<double>(suma) / n;
    std::cout << "El promedio es: " << promedio << std::endl;
    return 0;
}