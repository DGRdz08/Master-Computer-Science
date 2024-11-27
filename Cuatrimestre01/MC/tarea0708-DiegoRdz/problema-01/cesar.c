#include <stdio.h>

void decrypt(FILE *input, FILE *output, int shift) {
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (ch >= 'A' && ch <= 'Z') ch = 'A' + (ch - 'A' - shift + 26) % 26;
        fputc(ch, output);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        return 1;
    }


    FILE *Fpr = fopen(argv[1], "r");
    FILE *Fpr2 = fopen(argv[2], "w");

    if (Fpr == NULL || Fpr2 == NULL)    printf("No se puede abrir el archivo\n");
        
    int shift;
    printf("Introduzca el valor de desplazamiento para descifrar: ");
    scanf("%d", &shift);
    decrypt(Fpr, Fpr2, shift);
    printf("Descifrado realizado con éxito\n");

    fclose(Fpr);
    fclose(Fpr2);
    return 0;
}