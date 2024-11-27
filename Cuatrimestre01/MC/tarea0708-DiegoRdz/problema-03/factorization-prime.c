#include <stdio.h>
#define MAX_FACTORES 1000

// Función para verificar si un número es primo
int es_primo(int n) {
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

// Función para factorizar el número
int factorizacion(int n, int factores[]) {
    int cant_factores = 0;
    
    // Dividir por 2 hasta que ya no sea divisible
    while (n % 2 == 0) {
        factores[cant_factores++] = 2;
        n /= 2;
    }
    
    // Dividir por los números impares desde 3 en adelante
    for (int i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            factores[cant_factores++] = i;
            n /= i;
        }
    }
    
    // Si n es mayor que 1, es un factor primo
    if (n > 1) 
        factores[cant_factores++] = n;
    
    return cant_factores;
}

void imprimir_factores(int factores[], int cantidad) {
    printf("Factores: ");
    for (int i = 0; i < cantidad; i++) {
        printf("%d", factores[i]);
        if (i < cantidad - 1)
            printf(" × ");
    }
    printf("\n");
}

int main() {
    int factores[MAX_FACTORES];
    int numero;
    
    printf("Ingrese un número para factorizar: ");
    scanf("%d", &numero);
    
    if (numero <= 0) {
        printf("Solo se aceptan números positivos.\n");
        return 1;
    }
    
    int cantidad = factorizacion(numero, factores);
    imprimir_factores(factores, cantidad);    
    return 0;
}
