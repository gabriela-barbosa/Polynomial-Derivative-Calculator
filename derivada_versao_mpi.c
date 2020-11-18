#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <mpi.h>
#define TAM 12
int main(int argc, char* argv[])
{
        int id_Processo, quantidade_Processos,quantidade_a_ler,elementos_Recebidos;
        int p = 0;
        MPI_Init(&argc, &argv);
        double start = MPI_Wtime();
        int i, n,indice,index,grau = 0;
        MPI_Status status;
        MPI_Comm_rank(MPI_COMM_WORLD, &id_Processo);
        MPI_Comm_size(MPI_COMM_WORLD, &quantidade_Processos);
        float *polin,*deriv,*res,*aux;
        if(id_Processo == 0){
            char *fileAname= "ab.txt";
            FILE *fileA;
            fileA = fopen(fileAname,"r");
            if(!fileA)
                printf("Nome incorreto / arquivo nao encontrado!\n");
            else{
                printf("Arquivo encontrado.\n");
             }

           fscanf(fileA, "%d",&grau);
           polin = (float*)malloc(sizeof(float)*2*grau);
           deriv = (float*)malloc(sizeof(float)*2*grau);
           res = (float*)malloc(sizeof(float)*2*grau);

           quantidade_a_ler = grau / quantidade_Processos;

       for(i = 0;i<=grau;i++){
         fscanf(fileA,"%f", &polin[i]);

        }
        //Passando o grau para todos os processos
        MPI_Bcast(&grau,1,MPI_INT,0,MPI_COMM_WORLD);
        MPI_Scatter(polin,quantidade_a_ler,MPI_FLOAT,deriv,quantidade_a_ler,MPI_FLOAT,0,MPI_COMM_WORLD);
        //O processo mestre calcula a parte dele
        index =0;
        if(grau>quantidade_Processos*quantidade_a_ler){}
        for(i = 0;i<quantidade_a_ler;i++){
                res[i] = deriv[i]*index;
               // printf("P%d Derivada do q tem %f seria %f\n",id_Processo,deriv[i],deriv[i]*index);
           		index++;
           }
       /*  for(i = 0;i<quantidade_a_ler*quantidade_Processos;i++){
                polin[i] = 0;
           }*/
        //Pegando as partes dos escravos
         index = 1;
         int p = 1;
         for(i = quantidade_a_ler;i<quantidade_Processos*quantidade_a_ler;i++){

				MPI_Recv(&res[i], 1, MPI_FLOAT,index, 0,MPI_COMM_WORLD,&status);

                if(p == quantidade_a_ler){
                	index++;
                	p = 0;
                }
                p++;
         }
         //Por fim verificando se faltou alguma parte
      	if(quantidade_Processos*quantidade_a_ler<=grau){
      		for(p = quantidade_Processos*quantidade_a_ler;p<=grau;p++){
      			res[p] = polin[p]*p;
      		}

      	}
      	double end = MPI_Wtime();
      	printf("Tempo de execucao do algoritimo %f\n",end-start);
        }else{
           MPI_Bcast(&grau,1,MPI_INT,0,MPI_COMM_WORLD);
           polin = (float*)malloc(sizeof(float)*grau);
           deriv = (float*)malloc(sizeof(float)*grau);
           res = (float*)malloc(sizeof(float)*grau);
           quantidade_a_ler = grau / quantidade_Processos;
           MPI_Scatter(polin,quantidade_a_ler,MPI_FLOAT,deriv,quantidade_a_ler,MPI_FLOAT,0,MPI_COMM_WORLD);
           index = id_Processo*quantidade_a_ler-1;
           float aux = 0;
           for(i = 0;i<quantidade_a_ler;i++){
           		index++;
                aux = deriv[i]*index;
                MPI_Send(&aux,1,MPI_FLOAT, 0, 0,MPI_COMM_WORLD);
                //printf("aqui aaaaaaaaaaaaaprocesso %d ele %d , somando %f,\n",id_Processo,i,aux);
                // printf("P%d Derivada do q tem %f seria %f\n",id_Processo,deriv[i],deriv[i]*index);
           }

        }

    FILE *fp;

   fp = fopen("saida.txt", "w+");
   fprintf(fp, "%d\n",grau-1);

   if(id_Processo == 0){

      	for(i=0;i<=grau;i++){
      		 printf("Entrada = ");
      		 if(i!=0){fprintf(fp, "%f\n",res[i]);
      		 	printf("%f com x elevado a %d     ",polin[i],i);
      		 }else{fprintf(fp, "%f\n",res[i]);
      		 	printf("%f     ",polin[i]);
      		 }
      		printf("Saida = ");
     	 	if(i!=0){fprintf(fp, "%f\n",res[i]);
      		 	printf("%f com x elevado a %d\n",res[i],i-1);
      		 }else{fprintf(fp, "%f\n",res[i]);
      		 	printf("%f\n",res[i]);
      		 }
      	}
      }

  fclose(fp);

      MPI_Finalize();
      return 0;
}