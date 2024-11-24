#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>  
#include <cstdlib>
#include <ctime>
using namespace std;

// Función para generar un vector de edades ordenadas de menor a mayor
vector<int> generarEdadesOrdenadas(int n, int minEdad, int maxEdad) {
    vector<int> edades(n);
    for (int i = 0; i < n; ++i) {
        edades[i] = minEdad + rand() % (maxEdad - minEdad + 1);
    }
    sort(edades.begin(), edades.end());  // Ordenar el vector
    return edades;
}

// Función para generar un archivo de prueba
void generarCasoPrueba(const string& nombreArchivo, int x, int n, const vector<int>& edades) {
    ofstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al crear el archivo." << endl;
        return;
    }

    // Escribir la edad x a buscar
    archivo << x << endl;

    // Escribir el tamaño n del vector
    archivo << n << endl;

    // Escribir el vector de edades ordenadas
    for (int i = 0; i < n; ++i) {
        archivo << edades[i];
        if (i != n - 1) archivo << " ";  // Evitar el espacio al final de la última línea
    }
    archivo << endl;

    archivo.close();
    cout << "Archivo de prueba generado: " << nombreArchivo << endl;
}

int main() {
    srand(time(0));  // Semilla para generar números aleatorios

    // Parámetros generales
    int minEdad = 22;   // Edad mínima
    int maxEdad = 35;   // Edad máxima

    // Caso donde el resultado será True
    int nTrue = 200;     // Tamaño del vector
    int xTrue = 23;     // Edad mayoritaria a buscar
    vector<int> edadesTrue = generarEdadesOrdenadas(nTrue, minEdad, maxEdad);
    
    // Asegurar que xTrue aparezca más de n/2 veces
    for (int i = 0; i < nTrue / 2 + 1; ++i) {
        edadesTrue[i] = xTrue;
    }
    sort(edadesTrue.begin(), edadesTrue.end());  // Reordenar después de asignar

    // Generar archivo de prueba para el caso True
    generarCasoPrueba("prueba_true.txt", xTrue, nTrue, edadesTrue);

    // Caso donde el resultado será False
    int nFalse = 200;    // Tamaño del vector
    int xFalse = 25;    // Edad a buscar
    vector<int> edadesFalse = generarEdadesOrdenadas(nFalse, minEdad, maxEdad);
    
    // Asegurar que xFalse aparezca menos de n/2 veces
    for (int i = 0; i < nFalse / 2; ++i) {
        edadesFalse[i] = xFalse - 1;  // Poner valores menores a xFalse
    }
    sort(edadesFalse.begin(), edadesFalse.end());  // Reordenar después de asignar

    // Generar archivo de prueba para el caso False
    generarCasoPrueba("prueba_false.txt", xFalse, nFalse, edadesFalse);

    return 0;
}
