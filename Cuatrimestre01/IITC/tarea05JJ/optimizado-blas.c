#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cblas.h> // Incluye BLAS

// Función para generar matrices aleatorias
void generate_random_matrix(int n, double* M) {
    for (int i = 0; i < n * n; i++) {
        M[i] = (double)rand() / RAND_MAX * 10.0;
    }
}

// Función para imprimir matrices (opcional, solo para matrices pequeñas)
void print_matrix(int n, double* M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", M[i + j * n]);
        }
        printf("\n");
    }
}

int main() {
    int n = 2048;  // Tamaño de la matriz (debe ser lo suficientemente grande para ver mejoras)
    srand(time(NULL));

    // Reservar memoria para las matrices A, B y C
    double *A = (double*)malloc(n * n * sizeof(double));
    double *B = (double*)malloc(n * n * sizeof(double));
    double *C = (double*)malloc(n * n * sizeof(double));

    // Generar matrices aleatorias
    generate_random_matrix(n, A);
    generate_random_matrix(n, B);
    
    // Inicializar C a ceros
    for (int i = 0; i < n * n; i++) {
        C[i] = 0.0;
    }

    // Medir el tiempo de ejecución
    clock_t start = clock();
    
    // Multiplicación de matrices con BLAS (C = A * B)
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, 
                n, n, n, 1.0, A, n, B, n, 0.0, C, n);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tiempo de ejecucion con BLAS: %f segundos\n", time_spent);

    // Liberar memoria
    free(A);
    free(B);
    free(C);

    return 0;
}
