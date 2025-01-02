#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <locale.h>

int comp = 0;
int rotacao = 0;

//int main(int argc, char *argv[]) Para utilizar o terminal
int main()
{
    setlocale(LC_ALL, "Portuguese"); //habilita o portug�s
    pNodoA *raiz = NULL;
    char str1[20],str2[20];
    int ok = 0;
    int j = 0;

    char FiledictIn[30] ;
    char FileTextIn[30];
    char FileTextOut[30];
    char FileInfOut[30];

    strcpy(FiledictIn, "dict_10K.txt");
    strcpy(FileTextIn, "Alienista_cap1.txt");
    strcpy(FileTextOut, "Alienista_cap1Out.txt");

    //strcpy(FiledictIn, argv[1]);
    //strcpy(FileTextIn, argv[2]);
    //strcpy(FileTextOut, argv[3]);

    strcpy(FileInfOut, "InfoAVL.txt");


    //abre o arquivo dicion�rio para criar a �rvore
    FILE *arquivo = fopen(FiledictIn, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    //Cria o dicion�rio na �rvore
    while (fscanf(arquivo, " %19[^\t]\t%19[^\n]", str1, str2) == 2) //l� a palavra original e o sin�nimo
    {
        raiz = InsereAVL(raiz, str1, str2,&ok); //leva a insere AVL
        j++;
    }
    fclose(arquivo);


    FILE *arqlei = fopen(FileTextIn, "r");
    if (arqlei == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    FILE *arqesc = fopen(FileTextOut, "w");


    //Fun��o principal. Escreve novo arquivo substituindo as palavras com a �rvore dicion�rio
    //Recebe a �rvore, o arquivo original, e o arquivo de escrita
    escreveArquivo(raiz, arqlei, arqesc);

    fclose(arqlei);
    fclose(arqesc);


    FILE *arqinf = fopen(FileInfOut, "w");
        fprintf(arqinf, "===== Estat�sticas AVL ===== \n");
        fprintf(arqinf, "Arq entrada: %s\n", FileTextIn);
        fprintf(arqinf, "Arq dicion�rio: %s\n", FiledictIn);
        fprintf(arqinf, "N�mero de nodos: %d\n", j);
        fprintf(arqinf, "Altura: %d\n", altura(raiz));
        fprintf(arqinf, "Rota��es: %d\n", rotacao);
        fprintf(arqinf, "Compara��es: %d\n", comp);
    fclose(arqinf);


    return 0;
}
