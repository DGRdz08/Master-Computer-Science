/*****************************************
 ***Algoritmo: Intersección de Segmentos de Línea con Fuerza Bruta
 ***Autor: Diego Guadalupe Rodriguez Prieto
 ***Referencias:
                [1]  https://www.geeksforgeeks.org/how-to-create-vector-of-pairs-in-cpp/
                [2]  https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
                [3]  https://es.stackoverflow.com/questions/155475/imprimir-decimales-en-c
 ******************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

struct Point {
    int x;
    int y;
};

// Dado tres puntos colineales p, q, r, verifica si q está en el segmento 'pr'
bool onSegment(const Point& p, const Point& q, const Point& r) {
    return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
           q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y); // Verifica si q se encuentra en el segmento 'pr'
}

// Calcula la orientación de tres puntos (p, q, r)
int orientation(const Point& p, const Point& q, const Point& r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y); // Determinante
    if (val == 0) return 0; // colineal
    return (val > 0) ? 1 : 2; // horario o antihorario
}

// Verifica si dos segmentos p1q1 y p2q2 se intersectan
bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2, Point& intersection) {
    // Calcula las cuatro orientaciones necesarias para los casos generales y especiales
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // Caso general
    if (o1 != o2 && o3 != o4) {
        // Cálculo del punto de intersección
        float a1 = q1.y - p1.y;
        float b1 = p1.x - q1.x;
        float c1 = a1 * p1.x + b1 * p1.y;

        float a2 = q2.y - p2.y;
        float b2 = p2.x - q2.x;
        float c2 = a2 * p2.x + b2 * p2.y;

        float determinant = a1 * b2 - a2 * b1; 

        if (determinant != 0) { // Si los segmentos no son paralelos
            intersection.x = static_cast<int>((c1 * b2 - c2 * b1) / determinant); // Cálculo del punto de intersección
            intersection.y = static_cast<int>((a1 * c2 - a2 * c1) / determinant); 
            return true;
        }
    }

    // Casos especiales
    if (o1 == 0 && onSegment(p1, p2, q1)) { intersection = p2; return true; } // p1, q1 y p2 son colineales
    if (o2 == 0 && onSegment(p1, q2, q1)) { intersection = q2; return true; } // p1, q1 y q2 son colineales
    if (o3 == 0 && onSegment(p2, p1, q2)) { intersection = p1; return true; } // p2, q2 y p1 son colineales
    if (o4 == 0 && onSegment(p2, q1, q2)) { intersection = q1; return true; } // p2, q2 y q1 son colineales

    return false; // No hay intersección
}

int main() {
    int n;
    std::cin >> n;  // Número de segmentos
    std::vector<std::pair<Point, Point>> segments(n);
    clock_t start_time = clock();

    // Lectura de segmentos desde la entrada estándar
    for (int i = 0; i < n; ++i) {
        std::cin >> segments[i].first.x >> segments[i].first.y
                >> segments[i].second.x >> segments[i].second.y;
    }

    std::vector<Point> intersections;

    // Búsqueda de intersecciones
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            Point intersection;
            if (doIntersect(segments[i].first, segments[i].second,
                          segments[j].first, segments[j].second, intersection)) {
                intersections.push_back(intersection);
            }
        }
    }
    clock_t end_time = clock();
    // Escritura del resultado en la salida estándar
    std::cout << intersections.size() << "\n";
    for (const auto& pt : intersections) 
        std::cout << pt.x << " " << pt.y << "\n";

    double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << std::endl;
    std::cout << "Tiempo de ejecucion: " << std::fixed << std::setprecision(11) << execution_time << " segundos" << std::endl;
    return 0;
}