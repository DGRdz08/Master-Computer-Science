#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <chrono>  // Librería para medir tiempo

using namespace std;

int encontrarPrimeraRepetida(const vector<int>& U, int n) {
    unordered_set<int> edades_vistas;

    for (int i = 0; i < n; ++i) {
        // Si la edad ya está en el conjunto, es la primera repetida
        if (edades_vistas.find(U[i]) != edades_vistas.end()) {
            return U[i];  // La primera edad repetida
        }
        // Agregar la edad al conjunto de edades vistas
        edades_vistas.insert(U[i]);
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
