#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void dgemm(int n, double* A, double* B, double* C) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double cij = C[i + j * n];  // C[i][j]
            for (int k = 0; k < n; ++k) cij += A[i + k * n] * B[k + j * n];  // A[i][k] * B[k][j]
            C[i + j * n] = cij;  // Asignar el valor calculado a C[i][j]
        }
    }
}

void generate_random_matrix(int n, double* M) {
    for (int i = 0; i < n * n; ++i) {
        M[i] = (double)rand() / RAND_MAX * 10.0;  // Números aleatorios entre 0 y 10
    }
}

void print_matrix(int n, double* M) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) printf("%f ", M[i + j * n]);
        printf("\n");
    }
}
int main() {
    int n = 1024;  // Tamaño de las matrices
    srand(time(NULL));  // Semilla para generar números aleatorios
    
    // Reservar memoria para las matrices
    double* A = (double*)malloc(n * n * sizeof(double));
    double* B = (double*)malloc(n * n * sizeof(double));
    double* C = (double*)calloc(n * n, sizeof(double));  // Inicializada en 0
    
    // Generar matrices aleatorias
    generate_random_matrix(n, A);
    generate_random_matrix(n, B);
    
    clock_t start = clock();  // Inicio de medición de tiempo

    dgemm(n, A, B, C);  // Multiplicar matrices
    
    clock_t end = clock();  // Fin de medición de tiempo

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;    // Calcular el tiempo de ejecución
    printf("Tiempo de ejecucion: %f segundos\n", time_spent);

    // Liberar memoria
    free(A);
    free(B);
    free(C);

    return 0;
}