#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <chrono>

int main(int argc, char* argv[]) {
    auto start_time = std::chrono::high_resolution_clock::now();
    if (argc != 2) 
        std::cerr << "Uso: " << argv[0] << " <archivo_datos>\n";

    std::ifstream archivo(argv[1]);
    if (!archivo.is_open())
        std::cerr << "Error al abrir el archivo: " << argv[1] << "\n";


    int n, suma = 0;
    archivo >> n;

    if (n <= 0) 
        std::cerr << "Número inválido de elementos\n";


    std::vector<int> numeros(n);
    for (int i = 0; i < n; i++) {
        archivo >> numeros[i];
        suma += numeros[i];
    }
    archivo.close();

    double promedio = static_cast<double>(suma) / n;
    std::ostringstream resultFileName;
    resultFileName << "/shared_memory/resultados.txt";

    std::ofstream resultado(resultFileName.str(), std::ios_base::app);
    if (!resultado.is_open()) {
        std::cerr << "Error al escribir en el archivo de resultados\n";
        return 1;
    }
    resultado << "Archivo: " << argv[1] << ", Promedio: " << promedio << "\n";
    resultado.close();

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    std::cout << "Tiempo de procesamiento: " << duration.count() << " us\n";
    std::cout << "Procesado archivo: " << argv[1] << ", Promedio: " << promedio << "\n";

    return 0;
}
