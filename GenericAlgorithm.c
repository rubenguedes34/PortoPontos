#include "GenericAlgorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

/**
 *   Solução -> Diminuir o trajeto entre todos os locais a visitar
 *
 *       Melhores trajetos encontrados são selecionados para formar a próxima geração
 *       N gerações
 *
 *       Cada trajeto é representado por um array contendo IDs das cidades por ordem visita
 *       Cada trajeto calcula a distância total percorrida c/ distância entre cada par de locais vizinhos
 *
 *       População inicial é aleatória, escolher sequências de visita possiveis entre os locais a visitar usando permutações aleatórias
 *
 *       Gene- cidade
 *       Individuo- trajeto
 *       População - conjunto trajetos
 *       Pais      - 2 trajetos possiveis conbinam e criam 2 novos trajetos
 *       Selecao
 *       Cruzamento
 *       Mutação
 */

#define MAX 100
#define N 6    // nº cidades
#define P 10   // size população
#define Q 0.01 // probabilidade mutação
#define E 0    // nº individuos que passam por elitismo
#define G 0    // nº gerações


int main_generic() {


    int populacao[MAX][MAX];
    int trajeto[MAX];

    int distancias[MAX][MAX]; //Matriz quadrada com distâncias euclidianas,pré-calculadas,
    // entre pares de cidades

    char **currentGeneration, **nextGeneration; // globals

    currentGeneration = (char **) malloc(sizeof(char *) * P);
    nextGeneration = (char **) malloc(sizeof(char *) * P);

    for (int i = 0; i < G; i++) {

        for (int pop = 0; pop < P; pop++) {

        }


    }

}




int dist(COORDENADAS x1, COORDENADAS y1, COORDENADAS x2, COORDENADAS y2){


}

int aptidao(int T) {
    /* aptidao(T1) = 1 / (dist(C0,C1) + dist(C1, C2) + ... + dist(C4, C5) + dist(C5, C0));
    return 1 / ( dist(C0.coordenadas.x,C0.coordenadas.y,C1.coordenadas.x,C1.coordenadas.y)+ dist(C1.coordenadas.x,C1.coordenadas.y,C2.coordenadas.x,C2.coordenadas.y)+
    dist(C2.coordenadas.x,C2.coordenadas.y,C3.coordenadas.x,C3.coordenadas.y)+ dist(C3.coordenadas.x,C3.coordenadas.y,C4.coordenadas.x,C4.coordenadas.y)
    + dist(C4.coordenadas.x,C4.coordenadas.y,C5.coordenadas.x,C5.coordenadas.y)+ dist(C5.coordenadas.x,C5.coordenadas.y,C0.coordenadas.x,C0.coordenadas.y) ); */


}
