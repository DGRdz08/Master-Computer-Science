#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);
    int gcd;   

    if (argc < 3)       printf("Ingresa dos números.\n");

    for(int i=1; i <= n1 && i <= n2; ++i)
        if(n1%i==0 && n2%i==0) // Verificar si i es factor comun de n1 y n2
            gcd = i;

    printf("G.C.D de %d y %d es %d \n", n1, n2, gcd);

    return 0;
}
