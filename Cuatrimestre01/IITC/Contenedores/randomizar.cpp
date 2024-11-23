/*
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Autor: Diego Rodriguez
Fecha: 20/11/2024
Nombre: Generar numeros pseudoaleatorios con el algoritmo Generador Lineal Congruencial

Se debe de definir un "periodo" el cual nos definirá cada uno de los componentes y
la cantidad de numeros pseudoaleatorios que se pueden generar

X_n+1 = (a*X_n + c) mod m

donde
X_n es la semilla
m debe ser un numero primo grande o una potencia de 2 para que la distribucion sea uniforme
a es un multiplicador del tipo entero relativamente primo a m (no debe tener factores comunes con m)
c es un numero entero pequeño e impar para evitar periodicidad

int random (int m, int a, int c){
    int xn = time(NULL);
    return (xn * a + c) % m;
};

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*/
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<fstream>

int main(int argc, char const *argv[])
{   srand(time(NULL));
    int randomNumber = rand() % 10 - 1;
    int n = 10, m = 10;     //n es la cantidad de numeros pseudoaleatorios, m es el periodo
    int cantidadDeArchivos = 3; // cantidad de archivos a crear
    for (size_t i = 0; i < cantidadDeArchivos; i++)
    {
        std::string archivoNombre = "archivo_" + std::to_string(i) + ".txt";
        std::ofstream archivo(archivoNombre);
        if (archivo.is_open())
        {
            archivo << m << std::endl;
            for (int i = 0; i < n; i++)
            {  
                randomNumber = rand() % m - 1;
                archivo << randomNumber << std::endl;
            }
            archivo.close();        
            }
        else
        {
            std::cout << "Error al crear el archivo " << archivoNombre << std::endl;
        }
    }   
    return 0;
}