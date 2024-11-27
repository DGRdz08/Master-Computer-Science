#include <stdio.h>
#define MAX 1000000 // Asumimos que el i-ésimo primo estará dentro de este rango

void criba(unsigned char m[], int tam) {
    m[0] = 0;
    m[1] = 0;
    for(int i = 2; i <= tam; ++i)
        m[i] = 1;
    for(int i = 2; i*i <= tam; ++i)
        if(m[i])
            for(int h = 2; i*h <= tam; ++h)
                m[i*h] = 0;
}

int main() {
    int n, contador = 0; // El n-ésimo primo
    printf("Ingrese el n-ésimo primo: ");
    scanf("%d", &n);
    
    unsigned char esPrimo[MAX + 1];     // Crear y llenar el array para la criba
    criba(esPrimo, MAX);
    
    for(int i = 2; i <= MAX; i++) {
        if(esPrimo[i]) {
            contador++;
            if(contador == n) {
                printf("%d\n", i);
                return 0;
            }
        }
    }
    return 0;
}