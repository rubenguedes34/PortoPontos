#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Viagens        ////////////////////////////////////////////////
char ficheiro_viagens[]="viagens.txt";


void insert_viagens_dyn_array(CLASSVIAGENS *pcs,CIDADES cidadesvisitadas[],DATA date,int id,char nomeviag[]){

    /*int i=0;
    VIAGENS *viag=pcs->pointerviag;
    for (int j = 0; j < pcs->totalviagens && strcmp(cid,pcs->pointerviag->cidades.nome)!=0; j++){   //same city
        viag=viag->pnext;
    }
    if(viag==NULL)return;   */

    int i;
    VIAGENS *viag=pcs->pointerviag;
    viag->arrayviagens=(DYN_ARRAY_VIAGENS*)calloc(3, sizeof(DYN_ARRAY_VIAGENS));

    //caso seja a primeira viagem a ser inserida
    if(pcs->totalviagens==0){
        viag->id=id;
        viag->nomeviagem=(char*)malloc(strlen(nomeviag)+1);
        strcpy(viag->nomeviagem,nomeviag);
        viag->cidades.nome=(char*)malloc(strlen(cidadesvisitadas)+1);
        strcpy(viag->cidades.nome,cidadesvisitadas);
        viag->dataviagem=date;
        viag->arrayviagens->viagens_realizadas++;
        pcs->totalviagens++;
        return;
    }

    if (pcs->totalviagens==viag->arrayviagens->size){
        int oldSize=viag->arrayviagens->size, newSize=oldSize*2;
        pcs->pointerviag=(VIAGENS*)realloc(pcs->pointerviag,newSize* sizeof(VIAGENS));
        viag->arrayviagens->size=newSize;
        viag=pcs->pointerviag+oldSize;

        for (i = oldSize; i < newSize ; i++) {
            viag->id=0;
            viag->nomeviagem=NULL;
            viag->aptidao=0;
            viag->cidades.nome=NULL;
            viag->dataviagem.dia=0,viag->dataviagem.mes=0,viag->dataviagem.ano=0;
            viag++;

        }
        //voltar à posicao do antigo size para inserir aqui a viagem
        viag->id=id;
        viag->nomeviagem=(char*)malloc(strlen(nomeviag)+1);
        strcpy(viag->nomeviagem,nomeviag);
        viag->cidades.nome=(char*)malloc(strlen(cidadesvisitadas)+1);
        strcpy(viag->cidades.nome,cidadesvisitadas);
        viag->dataviagem=date;
        viag->arrayviagens->viagens_realizadas++;
        pcs->totalviagens++;
        return;
    }

    for (i = 0; i < viag->arrayviagens->size; i++) {
        if (viag->nomeviagem==NULL){
            viag->id=id;
            viag->nomeviagem=(char*)malloc(strlen(nomeviag)+1);
            strcpy(viag->nomeviagem,nomeviag);
            viag->cidades.nome=(char*)malloc(strlen(cidadesvisitadas)+1);
            strcpy(viag->cidades.nome,cidadesvisitadas);
            viag->dataviagem=date;
            viag->arrayviagens->viagens_realizadas++;
            pcs->totalviagens++;
            return;
        }
        viag++;
    }

}

void edit_viagens(VIAGENS *pcs,int id,DATA date){

}

void remove_viagens(VIAGENS *pcs,int id){

}

/**
 * Função print Viagens
 * @param pcs
 */
void print_viagens_dyn_array(CLASSVIAGENS pcs) {
    /*
    int i;
    while (viag != NULL) {
            while (i < viag->arrayviagens->size) {
                printf("\t&s[id=%d] aptidao:%d cidades:%s data:%d/%d/%d",viag->nomeviagem,viag->id,viag->aptidao,viag->cidades.nome,viag->dataviagem.dia,
                        viag->dataviagem.mes,viag->dataviagem.ano);
                viag++;
                i++;
            }
        }
        pcs.pointerviag->pnext;
        */
    VIAGENS *viag=pcs.pointerviag;
    if (pcs.pointerviag == NULL && pcs.totalviagens==0){     //não existem viagens
        printf("Nao existem viagens!!\n");
    }
    else {                                                  //print dados viagem
        printf("\tNumero de Viagens:%d\n", pcs.totalviagens);
        while (viag != NULL) {
            printf("Nome viagem:%s\n", viag->nomeviagem);
            printf("Id:%d\n", viag->id);
            printf("Cidades visitadas:%s\n", viag->cidades.nome);
            printf("Data:%d/%d/%d\n", viag->dataviagem.dia, viag->dataviagem.mes, viag->dataviagem.ano);
            viag = viag->pnext;
        }
    }
}
