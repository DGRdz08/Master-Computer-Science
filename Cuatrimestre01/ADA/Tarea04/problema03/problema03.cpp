#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

#define MAX 500
std::vector<int> ady[MAX];  //lista de adyacencia
std::vector<int> color;     //vector de colores (-1: sin color, 0: primer color, 1: segundo color)
int V;

bool isBipartite() {
    std::queue<int> q;
    color.assign(V, -1);  // Inicializar todos los vértices como no coloreados
    
    // Para manejar grafos desconectados, intentamos desde cada vértice no visitado
    for(int start = 0; start < V; start++) {
        if(color[start] == -1) {  // Si el vértice no ha sido coloreado
            color[start] = 0;     // Asignar el primer color
            q.push(start);
            
            while(!q.empty()) {
                int u = q.front();
                q.pop();
                
                // Revisar todos los vértices adyacentes
                for(int v : ady[u]) {
                    // Si el vértice adyacente no ha sido coloreado
                    if(color[v] == -1) {
                        color[v] = 1 - color[u];  // Asignar el color opuesto
                        q.push(v);
                    }
                    // Si el vértice adyacente tiene el mismo color, no es bipartito
                    else if(color[v] == color[u]) {
                        return false;
                    }
                }
            }
        }
    }
    
    return true;  // Si llegamos aquí, el grafo es bipartito
}

int main() {
    int E, x, y;
    std::cin >> V >> E;      // Número de vértices y aristas

    // Leer las aristas
    for(int i = 0; i < E; ++i) {
        std::cin >> x >> y;   // Origen y destino
        ady[x].push_back(y);
        ady[y].push_back(x);      // Por ser grafo no dirigido
    }

    clock_t start_time = clock();
    
    bool result = isBipartite();
    
    clock_t end_time = clock();
    double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;

    // Imprimir resultado
    std::cout << (result ? "Bipartita" : "No bipartita") << std::endl;
    std::cout << "Tiempo de ejecución: " << execution_time << " segundos" << std::endl;

    return 0;
}