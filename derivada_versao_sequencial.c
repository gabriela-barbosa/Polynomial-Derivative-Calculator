#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAM 12

int main(void) {
    int i, grau = 0;
    clock_t tic = clock();
    char *fileAname = "ab.txt";
    FILE *fileA;
    float *polin, *deriv;
    fileA = fopen(fileAname, "r");

    if (!fileA)
        printf("Nome incorreto / arquivo nao encontrado!\n");

    fscanf(fileA, "%d", &grau);

    FILE *fp;

   fp = fopen("saida.txt", "w+");
   fprintf(fp, "%d\n",grau-1);

    polin = (float *) malloc(sizeof(float) * grau);
    deriv = (float *) malloc(sizeof(float) * grau);
    for (i = 0; i <= grau; i++) {
        fscanf(fileA, "%f", &polin[i]);
    }
    for (i = 1; i <= grau; i++) {
        deriv[i-1] = polin[i] * i;
    }
       clock_t toc = clock();
    for (i = 0; i < grau; i++) {
        fprintf(fp, "%f\n",deriv[i]);
        printf("Elemento coeficiente %f, x elevado a %d \n", deriv[i], i);
    }


    printf("Execution time: %f \n", (double)(toc-tic)/CLOCKS_PER_SEC);
    return 0;
}