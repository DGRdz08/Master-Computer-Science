/*****************************************
 ***Algoritmo: Depth First Search Recursivo
 ***Autor: Diego Guadalupe Rodriguez Prieto
 ***Referencias: 
 ***            [1] https://github.com/jariasf/Online-Judges-Solutions/blob/master/Algorithms/C%2B%2B/Graph%20Theory/Algoritmo%20DFS%20usando%20Recursion.cpp
 ******************************************/
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 500

struct Edge {
    int destino;
    int peso;
};

std::vector<Edge> ady[MAX]; //lista de adyacencia con pesos
bool visitado[MAX];        //para nodos visitados
int V;                    //número de vértices
int path[MAX];           //para guardar el path actual
int bestPath[MAX];      //para guardar el mejor path
int maxDist;           //distancia máxima encontrada
int currentDist;      //distancia actual del recorrido
int bestLen;         //longitud del mejor camino
bool first;         //para formato de impresión

///Ver la ruta más larga usando DFS y backtracking
void dfs_longest(int u, int len) {
    visitado[u] = true;
    path[len] = u;                    //Almaceno en el path el vertice actual

    //Si encontramos un camino más largo, actualizamos
    if(currentDist > maxDist) {
        maxDist = currentDist;
        bestLen = len;
        for(int i = 0; i <= len; i++) {
            bestPath[i] = path[i];
        }
    }

    //Exploramos todos los vecinos
    for(size_t i = 0; i < ady[u].size(); i++) {
        int v = ady[u][i].destino; // valor agregado a la estructura
        if(!visitado[v]) {
            currentDist += ady[u][i].peso;           //agregamos el peso de la arista
            dfs_longest(v, len + 1);
            currentDist -= ady[u][i].peso;           //backtracking: quitamos el peso
            visitado[v] = false;                     //marcamos como no visitado para otros caminos
        }
    }
}

int main() {
    int E, x, y, w;
    
    std::cin >> V >> E;                    //Número de vértices y aristas
    
    //Lectura del grafo
    for(int i = 0; i < E; i++) {
        std::cin >> x >> y >> w;           //Origen, destino y peso
        ady[x].push_back({y, w});     //Solo agregamos en una dirección (grafo dirigido)
    }

    //Inicialización de variables
    maxDist = 0;
    currentDist = 0;
    bestLen = 0;

    //Probamos desde cada vértice como inicial
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < MAX; j++) {
            visitado[j] = false;  // Marcamos todos los vértices como no visitados
        }
        currentDist = 0;  // Reseteamos la distancia actual
        dfs_longest(i, 0);  // Llamamos a dfs_longest para iniciar la búsqueda desde el vértice i
    }


    //Impresión de resultados
    std::cout << "Distancia total: " << maxDist << std::endl;
    std::cout << "Ruta: ";
    first = true;
    for(int i = 0; i <= bestLen; i++) {
        if(first) {
            std::cout << bestPath[i];
            first = false;
        } else {
            std::cout << "->" << bestPath[i];
        }
    }
    std::cout << std::endl;

    return 0;
}