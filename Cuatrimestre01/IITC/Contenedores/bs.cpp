#include<iostream>

int count = 0;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
    count++;
}

void bubbleSort(int arr[], int n){
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

int main(){
    int A[7] = {1,2,3,4,5,6,7};
    bubbleSort(A, 7);
    for(int i = 0; i < 7; i++){
        std::cout << A[i] << std::endl;
    }

    std::cout << "Cantidad de intercambios: " << count << std::endl;
    return 0;
}