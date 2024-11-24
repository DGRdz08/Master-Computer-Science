#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>  // Librería para medir tiempo
using namespace std;

int encontrarPrimeraRepetida(const vector<int>& U, int n) {
    vector<int> edades_vistas;

    for (int i = 0; i < n; ++i) {
        // Buscar si la edad ya fue vista
        for (int j = 0; j < edades_vistas.size(); ++j) {
            if (edades_vistas[j] == U[i]) {
                return U[i];  // La primera edad repetida
            }
        }
        // Si no fue vista, agregarla a la lista de edades vistas
        edades_vistas.push_back(U[i]);
    }
    return -1;  // No hay elementos repetidos
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " archivo_de_entrada" << endl;
        return 1;
    }

    ifstream archivo(argv[1]);
    if (!archivo) {
        cerr << "No se puede abrir el archivo: " << argv[1] << endl;
        return 1;
    }

    int n;
    archivo >> n;

    auto start = chrono::high_resolution_clock::now();  // Tiempo inicial

    vector<int> U(n);


    // Leer las edades del archivo
    for (int i = 0; i < n; ++i) {
        archivo >> U[i];
    }

    archivo.close();

    // Encontrar la primera edad repetida
    int resultado = encontrarPrimeraRepetida(U, n);
    
    // Imprimir el resultado
    if (resultado != -1) {
        cout << resultado << endl;
    } else {
        cout << "No hay elementos repetidos" << endl;
    }

        auto end = chrono::high_resolution_clock::now();  // Tiempo final
    chrono::duration<double> duration = end - start;  // Duración

    cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << endl;

    return 0;
}