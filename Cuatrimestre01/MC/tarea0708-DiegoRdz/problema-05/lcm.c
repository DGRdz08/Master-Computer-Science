#include <stdio.h>
#include <stdlib.h>
#define MAX_FACTORES 1000

// Función para verificar si un número es primo
int es_primo(int n) {
    if (n <= 1) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) 
        if (n % i == 0 || n % (i + 2) == 0) return 0;
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
    if (n > 1) {
        factores[cant_factores++] = n;
    }
    return cant_factores;
}


// Función para encontrar el máximo exponente de un factor en un número
int max_exponente(int factor, int numero) {
    int exp = 0;
    while (numero % factor == 0) {
        exp++;
        numero /= factor;
    }
    return exp;
}

// Función para calcular el LCM de dos números
int calcular_lcm(int num1, int num2) {
    int lcm = 1;
    int factores_usados[MAX_FACTORES] = {0};
    int num_factores_usados = 0;
    
    // Obtenemos los factores primos de ambos números
    int factores1[MAX_FACTORES], factores2[MAX_FACTORES];
    int cant_factores1 = factorizacion(num1, factores1);
    int cant_factores2 = factorizacion(num2, factores2);
    
    // Recopilamos todos los factores únicos
    for (int i = 0; i < cant_factores1; i++) {
        int factor = factores1[i];
        int ya_usado = 0;
        
        for (int j = 0; j < num_factores_usados; j++) {
            if (factores_usados[j] == factor) {
                ya_usado = 1;
                break;
            }
        }
        
        if (!ya_usado)
            factores_usados[num_factores_usados++] = factor;
    }
    
    for (int i = 0; i < cant_factores2; i++) {
        int factor = factores2[i];
        int ya_usado = 0;
        
        for (int k = 0; k < num_factores_usados; k++) {
            if (factores_usados[k] == factor) {
                ya_usado = 1;
                break;
            }
        }
        
        if (!ya_usado) 
            factores_usados[num_factores_usados++] = factor;
    }
    
    // Para cada factor primo encontrado
    for (int i = 0; i < num_factores_usados; i++) {
        int factor = factores_usados[i];
        int exp1 = max_exponente(factor, num1);
        int exp2 = max_exponente(factor, num2);
        int max_exp;
        
        if (exp1 > exp2) 
            max_exp = exp1;
         else 
            max_exp = exp2;
        
        // Multiplicamos el LCM por el factor elevado al máximo exponente
        for (int j = 0; j < max_exp; j++) 
            lcm *= factor;
    }
    return lcm;
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

int main(int argc, char *argv[]) {
    // Verificar que se proporcionaron exactamente 2 argumentos
    if (argc != 3) {
        printf("Uso: %s <número1> <número2>\n", argv[0]);
        return 1;
    }
    
    // Convertir argumentos a enteros
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    
    // Verificar que los números son positivos
    if (num1 <= 0 || num2 <= 0) 
        printf("Solo se aceptan números positivos.\n");
    
    // Mostrar factorización de cada número
    int factores[MAX_FACTORES];
    printf("Factorización de %d:\n", num1);
    int cant_factores = factorizacion(num1, factores);
    imprimir_factores(factores, cant_factores);
    
    printf("Factorización de %d:\n", num2);
    cant_factores = factorizacion(num2, factores);
    imprimir_factores(factores, cant_factores);
    
    // Calcular e imprimir el LCM
    int lcm = calcular_lcm(num1, num2);
    printf("\nEl LCM de %d y %d es: %d\n", num1, num2, lcm);
    
    return 0;
}