#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <float.h>

using namespace std;

// Estructura para representar una instalación peligrosa
struct Installation {
    string name;
    int x, y;
};

// Función para calcular la distancia entre dos instalaciones
float dist(const Installation& a, const Installation& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Función para ordenar según coordenadas X
bool compareX(const Installation& a, const Installation& b) {
    return (a.x != b.x) ? (a.x < b.x) : (a.y < b.y);
}

// Función para ordenar según coordenadas Y
bool compareY(const Installation& a, const Installation& b) {
    return (a.y != b.y) ? (a.y < b.y) : (a.x < b.x);
}

// Función que implementa la solución Divide y Vencerás
pair<pair<Installation, Installation>, float> closestUtil(vector<Installation>& Px, vector<Installation>& Py) {
    int n = Px.size();

    // Caso base: Si hay 2 o 3 instalaciones, calcular directamente
    if (n <= 3) {
        float minDist = FLT_MAX; // Distancia infinita
        pair<Installation, Installation> result; // Par de instalaciones
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
    vector<Installation> Lx(Px.begin(), Px.begin() + mid);
    vector<Installation> Rx(Px.begin() + mid, Px.end());

    Installation midPoint = Px[mid];
    vector<Installation> Ly, Ry;

    for (auto& p : Py) {
        if ((p.x < midPoint.x) || (p.x == midPoint.x && p.y < midPoint.y))
            Ly.push_back(p);
        else
            Ry.push_back(p);
    }

    // Resolver recursivamente para ambas mitades
    auto leftResult = closestUtil(Lx, Ly);
    auto rightResult = closestUtil(Rx, Ry);

    // Combinar: Encontrar el menor resultado de ambas mitades
    pair<Installation, Installation> bestPair;
    float minDist;
    if (leftResult.second < rightResult.second) {
        minDist = leftResult.second;
        bestPair = leftResult.first;
    } else {
        minDist = rightResult.second;
        bestPair = rightResult.first;
    }

    // Considerar instalaciones cercanas a la línea divisoria
    vector<Installation> strip;
    for (auto& p : Py) {
        if (abs(p.x - midPoint.x) <= minDist)
            strip.push_back(p);
    }

    // Revisar el "strip" para encontrar posibles pares más cercanos
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < min(strip.size(), i + 7); ++j) {
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
pair<pair<Installation, Installation>, float> closest(vector<Installation>& installations) {
    vector<Installation> Px = installations;
    vector<Installation> Py = installations;

    sort(Px.begin(), Px.end(), compareX);
    sort(Py.begin(), Py.end(), compareY);

    return closestUtil(Px, Py);
}

int main() {
    // Leer el número de instalaciones
    int n;
    cin >> n;

    vector<Installation> installations(n);

    // Leer los datos de las instalaciones
    for (int i = 0; i < n; ++i) {
        cin >> installations[i].name >> installations[i].x >> installations[i].y;
    }

    // Resolver el problema
    auto result = closest(installations);
    auto pair = result.first;
    float distance = result.second;

    // Imprimir el resultado
    cout << fixed << setprecision(2);
    cout << "Las instalaciones que representan el mayor peligro son " << pair.first.name
         << " y " << pair.second.name << " (distancia " << distance << ")" << endl;

    return 0;
}