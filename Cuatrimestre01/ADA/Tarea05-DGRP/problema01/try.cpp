#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip> 
#include <float.h> 
#include<ctime>

//https://itzsyboo.medium.com/algorithms-studynote-4-divide-and-conquer-closest-pair-49ba679ce3c7

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(std::vector<int>& A, int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    int temp;
    for (int j = low; j < high; ++j)
    {
        if (A[j] < pivot)
        {
            i += 1;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return i + 1;
}

void quickSort(std::vector<int>& A, int low, int high) {
    if(low < high){
        // pi es el indice de la particion, A[pi] est en su lugar correcto
        int pi = partition (A, low, high);
        quickSort(A, low, pi - 1); 
        quickSort(A, pi + 1, high);
    }
}



// Estructura para representar una instalación peligrosa
struct Installation {
    std::string name;
    int x, y;
};

// Función para calcular la distancia entre dos instalaciones
float dist(const Installation& a, const Installation& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Función para ordenar según coordenadas X
/*
tomando dos instalaciones a y b, 
*/
bool compareX(const Installation& a, const Installation& b) {
    return (a.x != b.x) ? (a.x < b.x) : (a.y < b.y); // Si las coordenadas X son iguales, ordenar por Y
}

// Función para ordenar según coordenadas Y
bool compareY(const Installation& a, const Installation& b) {
    return (a.y != b.y) ? (a.y < b.y) : (a.x < b.x); // Si las coordenadas Y son iguales, ordenar por X
}

int partitionX(std::vector<Installation>& A, int low, int high) {
    Installation pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (compareX(A[j], pivot))
        {
            i += 1;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}
int partitionY(std::vector<Installation>& A, int low, int high) {
    Installation pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; ++j)
    {
        if (compareY(A[j], pivot))
        {
            i += 1;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}

void quickSortX(std::vector<Installation>& A, int low, int high) {
    if(low < high){
        // pi es el indice de la particion, A[pi] est en su lugar correcto
        int pi = partitionX(A, low, high);
        quickSortX(A, low, pi - 1); 
        quickSortX(A, pi + 1, high);
    }
}

void quickSortY(std::vector<Installation>& A, int low, int high) {
    if(low < high){
        // pi es el indice de la particion, A[pi] est en su lugar correcto
        int pi = partitionY(A, low, high);
        quickSortY(A, low, pi - 1); 
        quickSortY(A, pi + 1, high);
    }
}

// Función que implementa la solución Divide y Vencerás
std::pair<std::pair<Installation, Installation>, float> closestUtil(std::vector<Installation>& Px, std::vector<Installation>& Py) {
    int n = Px.size(); // Número de instalaciones en Px

    // Caso base: Si hay 2 o 3 instalaciones, calcular directamente
    if (n <= 3) {
        float minDist = FLT_MAX; // Distancia infinita
        std::pair<Installation, Installation> result; // Par de instalaciones
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {   
                float d = dist(Px[i], Px[j]);
                if (d < minDist) {
                    minDist = d;
                    result = {Px[i], Px[j]};
                }
            }
        }
        return {result, minDist};
    }

    // Dividir: Dividir las instalaciones en dos mitades
    int mid = n / 2;
    std::vector<Installation> Lx(Px.begin(), Px.begin() + mid); // Mitad izquierda
    std::vector<Installation> Rx(Px.begin() + mid, Px.end()); // Mitad derecha

    Installation midPoint = Px[mid]; // Punto medio
    std::vector<Installation> Ly, Ry; // Mitades de Py

    for (auto& p : Py) {
        if ((p.x < midPoint.x) || (p.x == midPoint.x && p.y < midPoint.y)) //  Si esta en la mitad izquierda o en el punto medio
            Ly.push_back(p); // Agregar a la mitad izquierda
        else
            Ry.push_back(p); // Agregar a la mitad derecha
    }

    // Resolver recursivamente para ambas mitades
    auto leftResult = closestUtil(Lx, Ly); // Encontrar el par de instalaciones más cercanas en la mitad izquierda
    auto rightResult = closestUtil(Rx, Ry); // Encontrar el par de instalaciones más cercanas en la mitad derecha

    // Combinar: Encontrar el menor resultado de ambas mitades
    std::pair<Installation, Installation> bestPair;
    float minDist;
    if (leftResult.second < rightResult.second) {
        minDist = leftResult.second;
        bestPair = leftResult.first;
    } else {
        minDist = rightResult.second;
        bestPair = rightResult.first;
    }

    // Considerar instalaciones cercanas a la línea divisoria
    std::vector<Installation> strip; // Instalaciones cercanas a la línea divisoria
    for (auto& p : Py) 
        if (abs(p.x - midPoint.x) <= minDist)
            strip.push_back(p);

    /* Revisar el "strip" para encontrar posibles pares más cercanos
    Se toma previamente la raiz cuadrada del tamaño de las instalaciones, 
    de modo que reduce la cantidad de pares a revisar a solo las 
    instalaciones en un radiocercanas 
    */
    int searchRadius = sqrt(n); 

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < std::min(strip.size(), i + searchRadius); ++j) {
            float d = dist(strip[i], strip[j]);
            if (d < minDist) {
                minDist = d;
                bestPair = {strip[i], strip[j]};
            }
        }
    }
    return {bestPair, minDist};
}

// Función principal para encontrar el par de instalaciones más cercanas
// Función principal para encontrar el par de instalaciones más cercanas
std::pair<std::pair<Installation, Installation>, float> closest(std::vector<Installation>& installations) {
    std::vector<Installation> Px = installations;
    std::vector<Installation> Py = installations;

    // Usar quickSort en lugar de std::sort
    quickSortX(Px, 0, Px.size() - 1); // Ordenar las instalaciones por coordenadas X
    quickSortY(Py, 0, Py.size() - 1); // Ordenar las instalaciones por coordenadas Y

    return closestUtil(Px, Py); // Devolver el par de instalaciones más cercanas
}

int main() {
    // Leer el número de instalaciones
    int n;
    clock_t start_time = clock();
    std::cin >> n;

    std::vector<Installation> installations(n);

    // Leer los datos de las instalaciones
    for (int i = 0; i < n; ++i) {
        std::cin >> installations[i].name >> installations[i].x >> installations[i].y;
    }

    // Resolver el problema
    auto result = closest(installations);
    auto pair = result.first;
    float distance = result.second;

    // Imprimir el resultado
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Las instalaciones que representan el mayor peligro son " << pair.first.name
         << " y " << pair.second.name << " (distancia " << distance << ")" << std::endl;
    clock_t end_time = clock();
    
    double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    return 0;
}