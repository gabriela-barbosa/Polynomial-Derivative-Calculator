#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAM 12

int main(void) {
    int i, grau = 0;
    clock_t before = clock();
    char *fileAname = "ab.txt";
    FILE *fileA;
    float *polin, *deriv;
    fileA = fopen(fileAname, "r");
    if (!fileA)
        printf("Nome incorreto / arquivo nao encontrado!\n");

    fscanf(fileA, "%d", &grau);
    polin = (float *) malloc(sizeof(float) * grau);
    deriv = (float *) malloc(sizeof(float) * grau);
    for (i = 0; i <= grau; i++) {
        fscanf(fileA, "%f", &polin[i]);
    }
    for (i = 1; i <= grau; i++) {
        deriv[i-1] = polin[i] * i;
    }
    for (i = 0; i < grau; i++) {
        printf("Elemento coeficiente %f, x elevado a %d \n", deriv[i], i);
    }
    clock_t difference = clock() - before;
    int msec = difference * 1000 / CLOCKS_PER_SEC;
    printf("Execution time: %dms \n", msec);
    return 0;
}