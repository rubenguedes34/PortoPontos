#include "GenericAlgorithm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/**
 *   Solução -> Diminuir o trajeto entre todos os locais a visitar
 *       Melhores trajetos encontrados são selecionados para formar a próxima geração
 *       N gerações
 *
 *       Cada trajeto é representado por um array contendo IDs das cidades por ordem visita
 *       Cada trajeto calcula a distância total percorrida c/ distância entre cada par de locais vizinhos

 *       Gene- cidade
 *       Individuo- trajeto
 *       População - conjunto trajetos
 *       Pais      - 2 trajetos possiveis conbinam e criam 2 novos trajetos
 *       Selecao
 *       Cruzamento
 *       Mutação
 */

#define MAX100 100
#define N 5     // nº cidades
#define P 2     // size população inicial
#define Q 0.01  // probabilidade mutação
#define E 1     // nº individuos que passam por elitismo
#define G 10    // nº gerações

CLASSCLIENTE clt = {NULL, 0};
CLASSVIAGENS_DYNARRAY viag={NULL, 0};
CLASSCIDADES_DYNARRAY cid = {NULL, 0};

int main_generic(){

    read_clientes_txt(&clt, "../data/clientes.txt");
    read_viagens_txt(&clt, "../data/viagens.txt");
    read_cidades_txt(&clt, "../data/cidades.txt");

    int trajeto1[N];        //cidades visitadas por ordem
    int trajeto2[N];

    create_initialpop(clt,"Viagem1",trajeto1,trajeto2);        //ViagemX indica set cidades a visitar no cidades_txt
    //aptidao(&clt,"Viagem1",trajeto2);




    return 0;
}


//Funções para inserir à cauda ou cabeça um nó de uma nova geração
//       de execução do AG; pesquisar uma geração pelo ID da iteração;
//pesquisar gerações com aptidão superior a um dado valor; etc.;
void insert_geracao_ordered(LL_GERACAO *llg,int id, int progenitoresg[N][N], int herdeirosg[N][N]){

}


/**
 * Função criar população inicial dado um viagem (viagem tem conjunto cidades visitadas)
 * @param cc
 * @param viagem
 * @param t1(array1)
 * @param t2(array2)
 */
void create_initialpop(CLASSCLIENTE cc, char viagem[], int t1[N], int t2[N]){
    CLIENTE *cliente=cc.pointerc;
    VIAGENS *aux=cliente->viagens.pointerviag;
    VIAGENS *viag=find_viagem_nome(cc, viagem);
    for (int i = 0; i < cc.totalclientes; i++) {       //pointer recebido de find_viagem só indica o pointer da viagem que queremos, temos de ver se o cliente coincide com esse pointer
        if(aux->nomeviagem==viag->nomeviagem){          //viagem pertence a este cliente
            break;
        }
        else if(cliente->viagens.n_viagens > 1){
            if(aux != viag) {//aux++;
                break;
            }
        }
        cliente=cliente->pnext;
    }
    //cliente e viagem já estão devidamente associados

    for (int i = 0; i< N; i++) {  //N== pviag->cidades_visitadas.n_cidades
        t1[i] = viag->cidades_visitadas.pointercid->ID;        //T1=array com ID's cidades visitadas
        t2[i] = viag->cidades_visitadas.pointercid->ID;        //T2=T1
        viag->cidades_visitadas.pointercid++;
    }
    /*for (int i = 0; i< N; i++) {       //N== pviag->cidades_visitadas.n_cidades
        t1[i] =  i;                      // usar ID's -> {0,1,2,3,4}
        t2[i] =  i;
    }*/

    shuffle_array(t2, N);     //T2=cidades visitas com random permutações aka ordem random

    printf("T1:");
    for (int j = 0; j < N; ++j) printf("%d ",t1[j]);
    printf("\nT2:");
    for (int j = 0; j < N; ++j) printf("%d ",t2[j]);
}

void shuffle_array(int arr[], int size){
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        int t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
    }
}

/**
 * Função calcular a distância entre 2 cidades
 * @param c0
 * @param c1
 */
float dist(COORDENADAS c0, COORDENADAS c1){
    return sqrtf( (c1.x - c0.x)*(c1.x - c0.x) + (c1.y - c0.y)*(c1.y - c0.y) );
    //sqrt{(c1.x-c0.x)^{2} + (c1.y-c0.y)^{2}}
}

/**
 * Função calcular aptidão de um trajeto, contem todas cidades visitadas
 * @param pcl
 * @param trajeto
 */
float aptidao(CLASSCLIENTE pcl,char viagem[],int trajeto[N]) {
    // aptidao(T1) = 1 / (dist(C0,C1) + dist(C1, C2) + ... + dist(C4, C5) + dist(C5, C0));

    CLIENTE *cliente=pcl.pointerc;
    VIAGENS *aux=cliente->viagens.pointerviag;
    VIAGENS *viag=find_viagem_nome(pcl, viagem);
    for (int i = 0; i < pcl.totalclientes; i++) {       //pointer recebido de find_viagem só indica o pointer da viagem que queremos, temos de ver se o cliente coincide com esse pointer
        if(aux->nomeviagem==viag->nomeviagem){          //viagem pertence a este cliente
            break;
        }
        else if(cliente->viagens.n_viagens > 1){
            if(aux != viag) {
                break;
            }
        }
        cliente=cliente->pnext;
    }

    for (int i = 0; i< N; i++) {  //N== pviag->cidades_visitadas.n_cidades
        trajeto[i] = viag->cidades_visitadas.pointercid->ID;        //T1=array com ID's cidades visitadas
        viag->cidades_visitadas.pointercid++;
    }

    CIDADES *cid=viag->cidades_visitadas.pointercid;
    CIDADES *cid_seguinte=cid++;
    float soma_dist=0.0f;

    while (cid_seguinte->nomecidade !=NULL) {                                   //ultima dist -> dist(C5,C0) not found
        soma_dist=soma_dist+dist(cid->coordenadas,cid_seguinte->coordenadas);
        cid++;
    }


    printf("%f",soma_dist);
    printf("%f",(1/soma_dist));
    return 1/soma_dist;
    // Para trajeto1[N]: aptidao(&clt,trajeto1) = 1/soma_dist
    //float soma_dist= ( dist(C0,C1)+ dist(C1,C2)+ dist(C2,C3)+ dist(C3,C4) + dist(C4,C5)+ dist(C5,C0) );
}






void radixsort(int vetor[], int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
            maior = vetor[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
        for (i = 0; i < tamanho; i++)
            bucket[(vetor[i] / exp) % 10]++;
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (i = tamanho - 1; i >= 0; i--)
            b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
        for (i = 0; i < tamanho; i++)
            vetor[i] = b[i];
        exp *= 10;
    }

    free(b);
}

void print_matrix_ints(int mNx100[][MAX100], int lines, int columns){

    for (int lin = 0; lin < lines; lin++) {
        for (int col = 0; col < columns; col++) {
            printf("%d", mNx100[lines][columns]);
        }
        printf("\n");
    }
}


void free_matrix(int m[MAX100][MAX100]){
    for(int i=0;i<N;i++) {
        free(m[i]);
    }

}