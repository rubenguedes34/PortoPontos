#include "GenericAlgorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *   Solução -> Diminuir o trajeto entre todos os locais a visitar
 *
 *       Melhores trajetos encontrados são selecionados para formar a próxima geração
 *       N gerações
 *
 *       Cada trajeto é representado por um array contendo IDs das cidades por ordem visita
 *       Cada trajeto calcula a distância total percorrida c/ distância entre cada par de locais vizinhos
 *
 *       População inicial é aleatória,
 *       A População Inicial de trajetos pode ser gerada de forma aleatória,ou seja,
 *       escolhendo sequências de visita possíveis entre os vários locais a visitar usando permutações aleatórias.
 *
 *       Gene- cidade
 *       Individuo- trajeto
 *       População - conjunto trajetos
 *       Pais      - 2 trajetos possiveis conbinam e criam 2 novos trajetos
 *       Selecao
 *       Cruzamento
 *       Mutação
 *
 */

#define MAX100 100
//#define N 6    // nº cidades
//#define P 6   // size população
#define Q 0.01 // probabilidade mutação
#define E 0    // nº individuos que passam por elitismo
//#define G 0    // nº gerações



int main_generic(int N, int P, int G){

    int populacao[MAX100][MAX100];
    int trajeto[MAX100];

    int distancias[MAX100][MAX100]; //Matriz quadrada com distâncias euclidianas,pré-calculadas,
    // entre pares de cidades


    //CIDADES *cidT1={.ID=0,.ID=1,.ID=2,.ID=3,.ID=4,.ID=5};
    //TRAJETO T1={1,cidT1,0};



}




int dist(COORDENADAS x1, COORDENADAS y1, COORDENADAS x2, COORDENADAS y2){


}

int aptidao(int T) {
    /* aptidao(T1) = 1 / (dist(C0,C1) + dist(C1, C2) + ... + dist(C4, C5) + dist(C5, C0));
    return 1 / ( dist(C0.coordenadas.x,C0.coordenadas.y,C1.coordenadas.x,C1.coordenadas.y)+ dist(C1.coordenadas.x,C1.coordenadas.y,C2.coordenadas.x,C2.coordenadas.y)+
    dist(C2.coordenadas.x,C2.coordenadas.y,C3.coordenadas.x,C3.coordenadas.y)+ dist(C3.coordenadas.x,C3.coordenadas.y,C4.coordenadas.x,C4.coordenadas.y)
    + dist(C4.coordenadas.x,C4.coordenadas.y,C5.coordenadas.x,C5.coordenadas.y)+ dist(C5.coordenadas.x,C5.coordenadas.y,C0.coordenadas.x,C0.coordenadas.y) ); */

}


//1º criar população(sabendo set cidades a visitar)
//      = gerar N individuos com genes ordenados de forma random
//       == gerar N Trajetos com ID's de cidades ordenados de forma random
//          Cada trajeto é representado por um array contendo IDs das cidades por ordem visita

/*void create_trajeto(int name, int size){    //array com IDs das cidades
    double *arrays[10];

    for (int i = 0; i < 6; i++)
        arrays[i] = malloc(size * sizeof(double));

} */

void create_initialpop(TRAJETO t,VIAGENS cid_a_visitar){

    int i, size;

    for ( i=0; i< 6; i++){
    }


}




void shuffle_array(int a[], int n){
    if (n > 1)
    {
        int i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = a[j];
            a[j] = a[i];
            a[i] = t;
        }
    }
}

void print_matrix_ints(int mNx100[][MAX100], int lines, int columns){

    for (int lin = 0; lin < lines; lin++) {
        for (int col = 0; col < columns; col++) {
            printf("%d", mNx100[lines][columns]);
        }
        printf("\n");
    }
}