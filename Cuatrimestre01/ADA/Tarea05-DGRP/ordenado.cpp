#include<iostream>

int main(){ 
    int n = 10000000;
    
    std::cout << n << std::endl;
    for(int i = 0; i < n; i++){
        std::cout << i + 1 << std::endl;
    }
    return 0;
}