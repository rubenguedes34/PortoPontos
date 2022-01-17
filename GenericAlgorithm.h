#ifndef PORTOPONTOS_GENERICALGORITHM_H
#define PORTOPONTOS_GENERICALGORITHM_H

#include "structs.h"
#include "functions.h"
#define MAX100 100
#define N 5  // nº cidades
#define P 2   // size população inicial
#define Q 0.01 // probabilidade mutação
#define E 1    // nº individuos que passam por elitismo
#define G 10   // nº gerações


typedef struct trajetos{
    int idtrajeto;
    int *trajeto;
    CLASSVIAGENS_DYNARRAY cidades;
    float dist_total;
}TRAJETO;

typedef struct geracoes{
    int idgeracao;
    int progenitores[MAX100][MAX100];
    int herdeiros[MAX100][MAX100];
    TRAJETO trajeto_mais_curto;
    struct geracoes *pnext;
}GERACAO;

typedef struct class_geracao{
    GERACAO *pointerg;
    int totalgeracoes;  //size
}LL_GERACAO;


int main_generic();
void create_initialpop(CLASSCLIENTE cc, char viagem[], int t1[N], int t2[N]);
void shuffle_array(int arr[], int size);
float dist(COORDENADAS c0, COORDENADAS c1);
float aptidao(CLASSCLIENTE pcl,char viagem[],int trajeto[N]);

void print_matrix_ints(int mNx100[][MAX100], int lines, int columns);
void radixsort(int vetor[], int tamanho);
void free_matrix(int m[MAX100][MAX100]);

#endif //PORTOPONTOS_GENERICALGORITHM_H
