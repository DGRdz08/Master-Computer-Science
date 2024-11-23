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


int LCG(int seed, int m, int a, int c) {
    return (a * seed + c) % m;
}

int main(int argc, char const *argv[]) {
    // Configurar los valores del rango y otros parámetros
    int L = 1, U = 100; // L: límite inferior, U: límite superior

    // Parámetros para el GLC
    int m = 101; // Debe ser un número primo grande o potencia de 2
    int a = 17;  // Multiplicador (relativamente primo a m)
    int c = 43;  // Incremento (impar y pequeño)
    int seed = time(NULL) % m; // Semilla inicial basada en el tiempo actual

    int n=10000000; // Cantidad de números pseudoaleatorios

    //generar 10 archivos
    for (int i = 0; i < 10; i++) {
        std::ofstream archivo;
        std::string filename = "random" + std::to_string(i + 1) + ".txt";
        archivo.open(filename);
        
        archivo<< n << std::endl;        
        // Generar los números pseudoaleatorios
        for (int j = 0; j < n; j++) {
            seed = LCG(seed, m, a, c);
            // Ajustar al rango [L, U]
            int randomNumber = L + seed % (U - L + 1); // rango [L, U]
            archivo << randomNumber << std::endl;
        }
        archivo.close();
    }
    return 0;
}
