#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <stdexcept>

// Generador de números aleatorios (Linear Congruential Generator)
int LCG(int seed, int m, int a, int c) {
    return (a * seed + c) % m;
}

// Función para generar archivos de datos
void generarArchivos(int L, int U, int m, int a, int c, int numArchivos, int elementosPorArchivo) {
    int seed = time(NULL) % m;
    
    for (int fileIndex = 0; fileIndex < numArchivos; ++fileIndex) {
        std::ostringstream fileName;
        fileName << "datos_" << fileIndex << ".txt";
        std::ofstream archivo(fileName.str());
        
        if (!archivo.is_open()) {
            std::cerr << "Error al crear el archivo: " << fileName.str() << "\n";
            continue;
        }
        
        archivo << elementosPorArchivo << std::endl;
        
        for (int i = 0; i < elementosPorArchivo; i++) {
            seed = std::abs(LCG(seed, m, a, c));
            int randomNumber = L + seed % (U - L + 1);
            archivo << randomNumber << std::endl;
        }
        
        archivo.close();
        std::cout << "Archivo generado: " << fileName.str() << "\n";
    }
}

// Función para procesar un archivo y calcular su promedio
double procesarArchivo(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    
    if (!archivo.is_open()) 
        std::cerr << "Error al abrir el archivo: " << rutaArchivo << "\n";
    
    int n, suma = 0;
    archivo >> n;
    
    if (n <= 0) 
        std::cerr << "Número inválido de elementos en " << rutaArchivo << "\n";
    
    std::vector<int> numeros(n);
    
    for (int i = 0; i < n; i++) {
        archivo >> numeros[i];
        suma += numeros[i];
    }
    
    archivo.close();
    
    return static_cast<double>(suma) / n;
}

int main() {
    // Parámetros de configuración
    int L = 1;                          // Límite inferior
    int U = 1000;                       // Límite superior
    int m = 2147483647;                 // Módulo para LCG
    int a = 48271;                      // Multiplicador para LCG
    int c = 0;                          // Incremento para LCG
    int numArchivos = 31;               // Número de archivos a generar
    int elementosPorArchivo = 1000000;  // Número de elementos por archivo

    auto inicio_total = std::chrono::high_resolution_clock::now();

    // Generar archivos de datos
    generarArchivos(L, U, m, a, c, numArchivos, elementosPorArchivo);

    // Abrir archivo de resultados
    std::ofstream resultado("resultados.txt", std::ios_base::app);
    
    if (!resultado.is_open())
        std::cerr << "Error al escribir en el archivo de resultados\n";

    // Procesar cada archivo generado
    double promedioTotal = 0.0;
    for (int fileIndex = 0; fileIndex < numArchivos; ++fileIndex) {
        std::ostringstream rutaArchivo;
        rutaArchivo << "datos_" << fileIndex << ".txt";
        
        auto inicio_archivo = std::chrono::high_resolution_clock::now();
        
        double promedio = procesarArchivo(rutaArchivo.str());
        promedioTotal += promedio;
        
        auto fin_archivo = std::chrono::high_resolution_clock::now();
        auto duracion_archivo = std::chrono::duration_cast<std::chrono::microseconds>(fin_archivo - inicio_archivo);
        
        resultado << "Archivo: " << rutaArchivo.str() 
                  << ", Promedio: " << std::fixed << std::setprecision(2) << promedio 
                  << ", Tiempo: " << duracion_archivo.count() << " us\n";
        
        std::cout << "Procesado archivo: " << rutaArchivo.str() 
                  << ", Promedio: " << std::fixed << std::setprecision(2) << promedio 
                  << ", Tiempo: " << duracion_archivo.count() << " us\n";
    }

    // Calcular promedio general
    double promedioFinal = promedioTotal / numArchivos;
    resultado << "\nPromedio General: " << std::fixed << std::setprecision(2) << promedioFinal << std::endl;
    std::cout << "\nPromedio General: " << std::fixed << std::setprecision(2) << promedioFinal << std::endl;

    resultado.close();

    auto fin_total = std::chrono::high_resolution_clock::now();
    auto duracion_total = std::chrono::duration_cast<std::chrono::milliseconds>(fin_total - inicio_total);
    
    std::cout << "Tiempo total de procesamiento: " << duracion_total.count() << " ms\n";

    return 0;
}