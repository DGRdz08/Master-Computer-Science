//https://www.geeksforgeeks.org/hoares-vs-lomuto-partition-scheme-quicksort/

#include <iostream>
#include <vector>
#include<ctime>

long long int count_swap = 0, count_comp = 0;

/* This function takes the last element as pivot, places
   the pivot element at its correct position in sorted
   array, and places all smaller (smaller than pivot)
   to the left of the pivot and all greater elements 
   to the right  of the pivot */


void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
    count_swap++;
}
int partition(std::vector<int>& arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1, j = high + 1;

    while (true) {
      
        // Find leftmost element greater than or
        // equal to pivot
        do {
            i++;
            count_comp++;
        } while (arr[i] < pivot);

        // Find rightmost element smaller than 
        // or equal to pivot
        do {
            j--;
            count_comp++;
        } while (arr[j] > pivot);

        // If two pointers met.
        if (i >= j){
            count_comp++;
            return j;
        }

        swap(&arr[i], &arr[j]);
    }
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(std::vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        count_comp++;
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Driver program to test above functions
int main()
{
    int n;
    clock_t start_time = clock();
    try
    {
        std::cin >> n;
        std::vector<int> arr(n);
        
        for (int i = 0; i < n; i++) // datos de entrada del vector
            std::cin >> arr[i];

        quickSort(arr, 0, n-1);
        std::cout << "Hoare Quicksort: \n";
        std::cout << "Total de swaps: "<< count_swap << std::endl;
        std::cout << "Total de comparaciones: " << count_comp << std::endl;    
         clock_t end_time = clock();
        double execution_time = double(end_time - start_time) / CLOCKS_PER_SEC;
        
        std::cout << "Tiempo de ejecucion: " << std::fixed  << execution_time << " segundos" << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}