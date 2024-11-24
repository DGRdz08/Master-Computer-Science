#include <iostream>  // Librería estándar para entrada y salida
#include <vector>    // Librería para trabajar con el contenedor vector
#include <fstream>   // Librería para manejo de archivos
#include <chrono>  // Librería para medir tiempo

using namespace std;

// Función para encontrar la primera aparición de x usando búsqueda lineal
int linearSearch(const vector<int>& S, int x) {
    // Recorremos el vector secuencialmente
    for (int i = 0; i < S.size(); i++) {
        if (S[i] == x) {  // Si encontramos x, retornamos el índice
            return i;
        }
    }
    return -1;  // Si no encontramos x, retornamos -1
}

// Función para verificar si la edad x es mayoritaria
bool edadMayoritaria(const vector<int>& S, int n, int x) {
    // Buscar la primera aparición de x en el vector S
    int primeraAparicion = linearSearch(S, x);
    
    if (primeraAparicion == -1) {  // Si no se encuentra x, retornamos false
        return false;
    }

    // Verificamos si x aparece en la posición (n/2) después de la primera aparición
    if (primeraAparicion + n / 2 < n && S[primeraAparicion + n / 2] == x) {
        return true;  // Si aparece más de n/2 veces, retornamos true
    }

    return false;  // Si no aparece más de n/2 veces, retornamos false
}

int main(int argc, char* argv[]) {
    // Abrimos el archivo de entrada usando el nombre pasado como argumento
    ifstream inputFile(argv[1]);
    
    // Verificamos si el archivo se abrió correctamente
    if (!inputFile) {
        cerr << "Error al abrir el archivo." << endl;  // Mostramos un mensaje de error si falla
        return 1;  // Terminamos el programa con un código de error
    }

    int x, n;  // Variables para la edad a buscar y el tamaño del vector
    inputFile >> x >> n;  // Leemos del archivo la edad x y el tamaño n

    // Medición de tiempo de ejecución
    auto start = chrono::high_resolution_clock::now();  // Tiempo inicial


    // Creamos un vector S de tamaño n
    vector<int> S(n);

    // Leemos del archivo los n números (edades) y los almacenamos en el vector S
    for (int i = 0; i < n; i++) {
        inputFile >> S[i];
    }

    // Llamamos a la función edadMayoritaria para verificar si x es mayoritaria
    if (edadMayoritaria(S, n, x)) {
        cout << "True" << endl;  // Si es mayoritaria, imprimimos True
    } else {
        cout << "False" << endl;  // Si no lo es, imprimimos False
    }

    auto end = chrono::high_resolution_clock::now();  // Tiempo final
    chrono::duration<double> duration = end - start;  // Duración

    cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << endl;


    return 0;
}
