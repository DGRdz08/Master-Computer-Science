import numpy as np
import time

def generate_random_matrix(n):
    return np.random.uniform(0, 10, size=(n, n))

def print_matrix(M):
    print(np.array2string(M, precision=6, suppress_small=True))

def main():
    n = 4096  # Tamaño de las matrices
    np.random.seed()  # Inicializar el generador de números aleatorios
    
    # Crear las matrices
    A = generate_random_matrix(n)
    B = generate_random_matrix(n)
    
    # Medir tiempo de ejecución
    start_time = time.time()
    
    # Multiplicación de matrices usando NumPy
    C = np.matmul(A, B)  # o simplemente: C = A @ B
    
    end_time = time.time()
    execution_time = end_time - start_time
    
    print(f"Tiempo de ejecución: {execution_time:.6f} segundos")

if __name__ == "__main__":
    main()