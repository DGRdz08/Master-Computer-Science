#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

int LCG(int seed, int m, int a, int c) {
    return (a * seed + c) % m;
}

int main() {
    // Configurar los valores del rango
    int L = 1, U = 1000000000; // Rango de los números aleatorios

    // Parámetros para el GLC
    int m = 2147483647; // Debe ser un número primo grande o potencia de 2
    int a = 48271;  // Multiplicador (relativamente primo a m)
    int c = 0;  // Incremento (impar y pequeño)
    int seed = time(NULL) % m; // Semilla inicial basada en el tiempo actual

    int n = 1000; // Cantidad de registros

    // Abrir archivo para escribir
    std::ofstream archivo("prueba1.txt");

    // Escribir cantidad de registros
    archivo << n << std::endl;

    // Generar datos
    for (int i = 0; i < n; i++) {
        seed = LCG(seed, m, a, c);
        int random1 = L + seed % (U - L + 1);
        seed = LCG(seed, m, a, c);
        int random2 = L + seed % (U - L + 1);

        archivo << "lugar" << (i + 1) << " " << random1 << " " << random2 << std::endl;
    }

    archivo.close();
    return 0;
}
