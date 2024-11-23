//quick sort

#include <iostream>
#include <vector>
#include<ctime>

int count_swap = 0, count_comp = 0;

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
    count_swap++;
}

int partition(std::vector<int>& A, int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    int temp;
    for (int j = low; j < high; ++j)
    {
        if (A[j] < pivot)
        {
            count_comp++;
            i += 1;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}

void quickSort(std::vector<int>& A, int low, int high) {
    if(low < high){
        // pi es el indice de la particion, A[pi] est en su lugar correcto
        int pi = partition (A, low, high);
        quickSort(A, low, pi - 1); 
        quickSort(A, pi + 1, high);
    }
}

int main() {
    int n;
    clock_t start_time = clock();
    try
    {
    std::cin >> n;
    std::vector<int> arr(n);
    
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    
    quickSort(arr, 0, n-1);

    std::cout << "Total de swaps:"<< count_swap << std::endl;

    clock_t end_time = clock();
    
    double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;
    
    std::cout << "Tiempo de ejecucion: " << std::fixed  << execution_time << " segundos" << std::endl;
    std::cout << "Total de comparaciones: " << count_comp << std::endl;
    }catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}