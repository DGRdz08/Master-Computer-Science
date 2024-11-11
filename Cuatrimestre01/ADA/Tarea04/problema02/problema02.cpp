/*****************************************
 
 ***Algoritmo: Depth First Search Recursivo
 ***Autor: Diego Guadalupe Rodriguez Prieto
 ***Referencias: 
 ***            [1] https://github.com/jariasf/Online-Judges-Solutions/blob/master/Algorithms/C%2B%2B/Graph%20Theory/Algoritmo%20DFS%20usando%20Recursion.cpp
 ******************************************/
#include <iostream>
#include <cstring>
#include <vector>
#include <tuple>
#include <ctime>

#define MAX 500 // Número de vértices
std::vector<std::tuple<int, int>> ady[MAX];  //lista de adyacencia (destino, peso)
bool visitado[MAX];    //para nodos visitados
int V;
int path[MAX];         //para guardar el path actual
int maxPath[MAX];      //para guardar el path más largo encontrado
int maxLen = -1;       //longitud del path más largo
int maxDistance = -1;  //distancia máxima encontrada

void dfs_longest_path(int u, int fin, int len, int currentDistance) {
    visitado[u] = true;
    path[len] = u;  // Almaceno el vértice actual en el path

    if(u == fin) {
        if(currentDistance > maxDistance) {
            maxDistance = currentDistance;
            maxLen = len;
            // Guardar el path actual como el mejor path
            for(int i = 0; i <= len; i++) {
                maxPath[i] = path[i];
            }
        }
        return;
    }

    // Recorrer adyacentes como en tu código original
    for(int i = 0; i < ady[u].size(); ++i) {
        auto [v, weight] = ady[u][i];
        if(!visitado[v]) {
            dfs_longest_path(v, fin, len + 1, currentDistance + weight);
            visitado[v] = false;  // Backtracking como en tu código
        }
    }
}

int main() {
    int E, x, y, w;
    scanf("%d %d", &V, &E);

    for(int i = 0; i < E; ++i) {
        scanf("%d %d %d", &x, &y, &w);
        ady[x].push_back(std::make_tuple(y, w));
        ady[y].push_back(std::make_tuple(x, w));
    }

    // Variables para guardar la ruta más larga global
    int globalMaxDistance = -1;
    int globalMaxPath[MAX];
    int globalMaxLen = -1;
    int start_vertex = -1, end_vertex = -1;
    
    clock_t start_time = clock();

    // Probar todas las combinaciones de vértices
    for(int i = 0; i < V; i++) {
        for(int j = i + 1; j < V; j++) {
            memset(visitado, 0, sizeof(visitado));
            maxDistance = -1;
            maxLen = -1;
            
            dfs_longest_path(i, j, 0, 0);
            
            if(maxDistance > globalMaxDistance) {
                globalMaxDistance = maxDistance;
                globalMaxLen = maxLen;
                for(int k = 0; k <= maxLen; k++) {
                    globalMaxPath[k] = maxPath[k];
                }
                start_vertex = i;
                end_vertex = j;
            }
        }
    }

    clock_t end_time = clock();
    double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    // Imprimir resultados
    printf("Distancia total de la ruta mas larga: %d\n", globalMaxDistance);
    printf("Ruta mas larga: ");
    for(int i = 0; i <= globalMaxLen; i++) {
        if(i > 0) printf("->");
        printf("%d", globalMaxPath[i]);
    }
    printf("\n");
    printf("Tiempo de ejecucion: %.8f segundos\n", execution_time);

    return 0;
}