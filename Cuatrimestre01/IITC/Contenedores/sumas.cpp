#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream archivo("/shared_memory/datos.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo\n";
        return 1;
    }

    int n, suma = 0;
    archivo >> n;
    std::vector<int> numeros(n);

    for (int i = 0; i < n; i++) {
        archivo >> numeros[i];
        suma += numeros[i];
    }

    archivo.close();
    std::cout << "El promedio es: " << (suma / n) << std::endl;
    return 0;
}