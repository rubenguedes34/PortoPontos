#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Viagens        ////////////////////////////////////////////////
char ficheiro_viagens[]="viagens.txt";

void create_dynarray_classviagens(CLASSVIAGENS_DYNARRAY *pcs,int size){
    pcs->pointerviag=(VIAGENS*) calloc(size,sizeof(VIAGENS));
    pcs->totalviagens=size;
    pcs->current_viagem=0;
}

/* void insert_viagens_dyn_array(CLASSVIAGENS_DYNARRAY *pcs, CIDADES cidadesvisitadas[], DATA date, int id, char nomeviag[]){

    int i=0;
    VIAGENS *viag=pcs->pointerviag;
    for (int j = 0; j < pcs->totalviagens && strcmp(cid,pcs->pointerviag->cidades.nome)!=0; j++){   //same city
        viag=viag->pnext;
    }
    if(viag==NULL)return;

    int i;
    VIAGENS *viag=pcs->pointerviag;

    //caso seja a primeira viagem a ser inserida
    if(pcs->totalviagens==0){
        viag->id=id;
        viag->pnomeviagem=(char*)malloc(strlen(nomeviag) + 1);
        strcpy(viag->pnomeviagem, nomeviag);
        viag->cidades.nome=(char*)malloc(strlen(cidadesvisitadas)+1);
        strcpy(viag->cidades.nome,cidadesvisitadas);
        viag->dataviagem=date;
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
            viag->pnomeviagem=NULL;
            viag->cidades.nome=NULL;
            viag->dataviagem.dia=0,viag->dataviagem.mes=0,viag->dataviagem.ano=0;
            viag++;

        }
        //voltar à posicao do antigo size para inserir aqui a viagem
        viag->id=id;
        viag->pnomeviagem=(char*)malloc(strlen(nomeviag) + 1);
        strcpy(viag->pnomeviagem, nomeviag);
        viag->cidades.nome=(char*)malloc(strlen(cidadesvisitadas)+1);
        strcpy(viag->cidades.nome,cidadesvisitadas);
        viag->dataviagem=date;
        viag->arrayviagens->viagens_realizadas++;
        pcs->totalviagens++;
        return;
    }

    for (i = 0; i < viag->arrayviagens->size; i++) {
        if (viag->pnomeviagem == NULL){
            viag->id=id;
            viag->pnomeviagem=(char*)malloc(strlen(nomeviag) + 1);
            strcpy(viag->pnomeviagem, nomeviag);
            viag->cidades.nome=(char*)malloc(strlen(cidadesvisitadas)+1);
            strcpy(viag->cidades.nome,cidadesvisitadas);
            viag->dataviagem=date;
            viag->arrayviagens->viagens_realizadas++;
            pcs->totalviagens++;
            return;
        }
        viag++;
    }

} */

void insert_viagens_dyn_array(CLASSVIAGENS_DYNARRAY *pcs, CLASSVIAGENS_DYNARRAY cidadesvisitadas[], DATA date, int id, char nomeviag[]){
    VIAGENS *viag=NULL;
    CIDADES c0={0,NULL,NULL,0.0f,0.0f,NULL,0};
    VIAGENS viagem0={0,NULL,c0,0,0,0};

    if(pcs->current_viagem==pcs->totalviagens){ //está full, precisamos de resize
        int oldsize=pcs->totalviagens;
        int newsize=oldsize+10;
        pcs->pointerviag=(VIAGENS*) realloc(pcs->pointerviag,newsize*sizeof(VIAGENS));
        pcs->totalviagens=newsize;
        for (int i = 0; i < oldsize; i++) {
            *(pcs->pointerviag+i)=viagem0;
        }

    }
    else{   //inserção direta
        viag=pcs->pointerviag+pcs->current_viagem;
        pcs->pointerviag->id=id;
        viag->pnomeviagem=(char*)malloc(sizeof(strlen(nomeviag)+1));
        strcpy(pcs->name, nomeviag);
        viag->cidades.nome=(char*)malloc(sizeof(strlen(cidadesvisitadas)+1));
        strcpy(viag->cidades.nome,cidadesvisitadas);
        pcs->pointerviag->dataviagem=date;
        pcs->current_viagem++;
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
void print_viagens_dyn_array(CLASSVIAGENS_DYNARRAY pcs) {

    if (pcs.pointerviag == NULL && pcs.totalviagens==0){     //não existem viagens
        printf("Nao existem viagens!!\n");
    }
    else {                                                  //print dados viagem
        printf("\tNumero de Viagens:%d\n", pcs.totalviagens);
        for (int i = 0; i < pcs.totalviagens; i++) {
            printf("Nome viagem:%s\n", pcs.name);
            printf("Id:%d\n", pcs.pointerviag->id);
            printf("Cidades visitadas:%s\n", pcs.pointerviag->cidades.nome);
            printf("Data: %d/%d/%d\n\n", pcs.pointerviag->dataviagem.dia,pcs.pointerviag->dataviagem.mes,pcs.pointerviag->dataviagem.ano);
            pcs.pointerviag++;
        }

    }
}
