#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <malloc.h>

// Asumimos que n es múltiplo de 4 para simplificar el código
// gcc -mavx2 -mfma -O3 optimized.c -o prog
void dgemm_avx(int n, double* A, double* B, double* C) {
    for (int i = 0; i < n; i += 4) {
        for (int j = 0; j < n; j++) {
            __m256d c0 = _mm256_load_pd(&C[i + j * n]); // Cargar 4 elementos de C

            for (int k = 0; k < n; k++) {
                __m256d a0 = _mm256_load_pd(&A[i + k * n]); // Cargar 4 elementos de A
                __m256d b0 = _mm256_broadcast_sd(&B[k + j * n]); // Broadcast de B[k][j]
                c0 = _mm256_fmadd_pd(a0, b0, c0); // c0 += a0 * b0
            }

            _mm256_store_pd(&C[i + j * n], c0); // Guardar resultado en C
        }
    }
}

void generate_aligned_random_matrix(int n, double** M) {
    // Usar _aligned_malloc para Windows
    *M = (double*)_aligned_malloc(n * n * sizeof(double), 32);
    if (*M == NULL) {
        printf("Error en la alineación de memoria\n");
        exit(1);
    }
    
    for (int i = 0; i < n * n; i++) {
        (*M)[i] = (double)rand() / RAND_MAX * 10.0;
    }
}

void print_matrix(int n, double* M) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ", M[i + j * n]);
        }
        printf("\n");
    }
}

int main() {
    // El tamaño de la matriz debe ser múltiplo de 4 para AVX
    int n = 2048;
    srand(time(NULL));

    double *A, *B, *C;
    
    // Generar matrices alineadas
    generate_aligned_random_matrix(n, &A);
    generate_aligned_random_matrix(n, &B);
    generate_aligned_random_matrix(n, &C);
    
    // Inicializar C en ceros
    for (int i = 0; i < n * n; i++) {
        C[i] = 0.0;
    }

    clock_t start = clock();
    
    dgemm_avx(n, A, B, C);
    
    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    
    printf("Tiempo de ejecucion: %f segundos\n", time_spent);

    // Liberar memoria usando _aligned_free para Windows
    _aligned_free(A);
    _aligned_free(B);
    _aligned_free(C);

    return 0;
}