/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Autor: Diego Rodriguez
Fecha: 20/11/2024
Nombre: Generar numeros pseudoaleatorios con el algoritmo Generador Lineal Congruencial

Se debe de definir un "periodo" el cual nos definirá cada uno de los componentes y
la cantidad de numeros pseudoaleatorios que se pueden generar

X_n+1 = (a*X_n + c) mod m

donde
X_n es la semilla
m debe ser un numero primo grande o una potencia de 2 para que la distribucion sea uniforme
a es un multiplicador del tipo entero relativamente primo a m (no debe tener factores comunes con m)
c es un numero entero pequeño e impar para evitar periodicidad

int random (int m, int a, int c){
    int xn = time(NULL);
    return (xn * a + c) % m;
};

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iomanip>

int LCG(int seed, int m, int a, int c) {
    return (a * seed + c) % m;
}

int main() {
    int L = 1, U = 1000;
    int m = 2147483647, a = 48271, c = 0;
    int seed = time(NULL) % m;
    int n = 1000000; // Número de elementos
    
    int numArchivos = 31;  // Número de archivos a generar

    for (int fileIndex = 0; fileIndex < numArchivos; ++fileIndex) {
        std::ostringstream fileName;
        fileName << "/shared_memory/datos_" << fileIndex << ".txt";
        std::ofstream archivo(fileName.str());
        if (!archivo.is_open()) {
            std::cerr << "Error al crear el archivo: " << fileName.str() << "\n";
            return 1;
        }

        archivo << n << std::endl;
        for (int i = 0; i < n; i++) {
            seed = std::abs(LCG(seed, m, a, c));
            int randomNumber = L + seed % (U - L + 1);
            archivo << randomNumber << std::endl;
        }
        archivo.close();
        std::cout << "Archivo generado: " << fileName.str() << "\n";
    }
    return 0;
}
