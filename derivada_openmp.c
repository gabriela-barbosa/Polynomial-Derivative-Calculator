#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>


int main(void) {
    printf("Quantidade de threads : \n");
    int tt;
    scanf("%d", &tt);
    int i, grau = 0;
    double tic = omp_get_wtime();
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
    #pragma omp parallel for num_threads(tt)
    for (i = 1; i <= grau; i++) {
        #pragma omp critical
        deriv[i-1] = polin[i] * i;
    }
       double toc = omp_get_wtime();

    for (i = 0; i < grau; i++) {
        fprintf(fp, "%f\n",deriv[i]);
        printf("Elemento coeficiente %f, x elevado a %d \n", deriv[i], i);
    }


    printf("Execution time: %lf \n",toc-tic);
    return 0;
}