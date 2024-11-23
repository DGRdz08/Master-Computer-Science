#include<iostream>
#include<vector>

int main()
{
    std::vector<int> lista;
    int numero;
    while (std::cin >> numero)
        lista.push_back(numero); // Agregar el número leído a la lista

    float r = 0.0;
    // Imprimir la lista leída
    for (int i = 0; i < lista.size(); i++) 
        r += lista[i];
    
    std::cout << r/lista.size() << std::endl;

    return 0;
}