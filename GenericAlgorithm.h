#ifndef PORTOPONTOS_GENERICALGORITHM_H
#define PORTOPONTOS_GENERICALGORITHM_H

#include "structs.h"
#define MAX100 100

//Para isso devemos ir recolhendo numa lista ligada,informação ao longo da execução do AG
// (e.g.Indivíduo mais apto(trajetória mais curta) e respectiva distância em cada geração).

typedef struct trajetos{
    int idtrajeto;
    CIDADES *cid;
    float dist_total;
}TRAJETO;

typedef struct ll_geracoes{
    int idgeracao;
    int progenitores[MAX100][MAX100];
    int herdeiros[MAX100][MAX100];
    TRAJETO trajeto_mais_curto;
    struct ll_geracoes *pnext;
}GERACAO;


int main_generic();
void create_initialpop(TRAJETO t,VIAGENS cid_a_visitar);

int dist(COORDENADAS x1, COORDENADAS y1, COORDENADAS x2, COORDENADAS y2);
int aptidao(int T);
void shuffle_array(int a[], int n);
void print_matrix_ints(int mNx100[][MAX100], int lines, int columns);

#endif //PORTOPONTOS_GENERICALGORITHM_H
