import random
import time

def dgemm(n, A, B, C):
    for i in range(n):
        for j in range(n):
            cij = C[i * n + j]  # C[i][j]
            for k in range(n):
                cij += A[i * n + k] * B[k * n + j]  # A[i][k] * B[k][j]
            C[i * n + j] = cij  # Asignar el valor calculado a C[i][j]

def generate_random_matrix(n):
    return [random.uniform(0, 10) for _ in range(n * n)]

def print_matrix(n, M):
    for i in range(n):
        for j in range(n):
            print(f"{M[i * n + j]:.6f}", end=" ")
        print()

def main():
    n = 4096  # Tamaño de las matrices
    random.seed()  # Inicializar el generador de números aleatorios
    
    # Crear las matrices
    A = generate_random_matrix(n)
    B = generate_random_matrix(n)
    C = [0.0] * (n * n)  # Matriz C inicializada en 0
    
    # Medir tiempo de ejecución
    start_time = time.time()
    
    dgemm(n, A, B, C)
    
    end_time = time.time()
    execution_time = end_time - start_time
    
    print(f"Tiempo de ejecución: {execution_time:.6f} segundos")

if __name__ == "__main__":
    main()