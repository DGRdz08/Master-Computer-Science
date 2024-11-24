#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm> 
#include <numeric>   

using namespace std;

// Función para generar un archivo de texto con un vector de edades
void generarArchivo(const string& nombre_archivo, const vector<int>& edades) {
    ofstream archivo(nombre_archivo);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << nombre_archivo << endl;
        return;
    }

    archivo << edades.size() << endl;
    for (size_t i = 0; i < edades.size(); ++i) {
        archivo << edades[i] << " ";
    }
    archivo.close();
}

// Función para generar un vector con edades repetidas dentro de un rango
vector<int> generarConRepetidos(int n, int min_edad, int max_edad) {
    vector<int> edades(n);
    int rango = max_edad - min_edad + 1;
    
    for (int i = 0; i < n - 1; ++i) {
        edades[i] = min_edad + (rand() % rango);
    }
    // Añadimos un valor repetido al final
    edades[n - 1] = edades[rand() % (n - 1)];
    return edades;
}

// Función para generar un vector sin elementos repetidos dentro de un rango
vector<int> generarSinRepetidos(int n, int min_edad, int max_edad) {
    vector<int> edades(max_edad - min_edad + 1);
    iota(edades.begin(), edades.end(), min_edad); // Llena el vector con valores en el rango

    // Barajamos el vector para asegurar que los elementos estén en orden aleatorio
    random_shuffle(edades.begin(), edades.end());

    // Reducción del tamaño del vector si es necesario
    if (n < edades.size()) {
        edades.resize(n);
    }
    return edades;
}

int main() {
    srand(time(0)); // Inicializa la semilla para números aleatorios

    int n = 2000; // Tamaño del vector
    int min_edad = 20; // Edad mínima
    int max_edad = 30; // Edad máxima

    // Generar el archivo con edades repetidas
    vector<int> edades_repetidas = generarConRepetidos(n, min_edad, max_edad);
    generarArchivo("con_repetidos.txt", edades_repetidas);

    // Generar el archivo con edades sin repetir
    vector<int> edades_sin_repetidos = generarSinRepetidos(n, min_edad, max_edad);
    generarArchivo("sin_repetidos.txt", edades_sin_repetidos);

    cout << "Archivos de prueba generados exitosamente." << endl;

    return 0;
}
