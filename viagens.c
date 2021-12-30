#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Viagens        ////////////////////////////////////////////////

void create_dynarray_classviagens(CLASSVIAGENS_DYNARRAY *pcv, int init_size){
    VIAGENS *pviag = (VIAGENS*)calloc(init_size, sizeof(VIAGENS));
    pcv->pointerviag=pviag;
    pcv->totalviagens=init_size;
    //printf("Dyn array created!\tSize:%d\n\n",init_size);
}


void insert_viagens_dyn_array(CLASSVIAGENS_DYNARRAY *pcv, char nomeviag[], char cidadesvisitadas[], DATA date, int id) {
    int i = 0;
    VIAGENS *pviag = pcv->pointerviag;
    for (; i < pcv->totalviagens; i++) {
        if (pviag->pnomeviagem == NULL) {
            //printf("Insercao direta!\n");
            pviag->pnomeviagem = (char *) malloc(strlen(nomeviag) + 1);
            strcpy(pviag->pnomeviagem, nomeviag);
            //printf("Nome:%s\n",nomeviag);
            pviag->cidades_a_visitar=(char*)malloc(strlen(cidadesvisitadas)+1);
            strcpy(pviag->cidades_a_visitar,cidadesvisitadas);
            //printf("Cidades:%s\n",cidadesvisitadas);
            pviag->dataviagem = date;
            pviag->id = id;
            //printf("ID:%d\n\n",id);
            return;
        }
        pviag++;
    }
    if (i == pcv->totalviagens) {
        int oldsize = pcv->totalviagens;
        int newsize = oldsize + 5;
        pcv->pointerviag = (VIAGENS *) realloc(pcv->pointerviag, newsize * sizeof(VIAGENS));
        pcv->totalviagens = newsize;
        pviag = pcv->pointerviag + oldsize;
        for (i = oldsize; i < newsize; i++){
            pviag->pnomeviagem = NULL;
            pviag->cidades_a_visitar=NULL;
            pviag->dataviagem.dia=0,pviag->dataviagem.mes=0,pviag->dataviagem.ano=0;
            pviag->id = 0;
            pviag++;
        }
        pviag= pcv->pointerviag+oldsize;
        pviag->pnomeviagem = (char *) malloc(strlen(nomeviag) + 1);
        strcpy(pviag->pnomeviagem, nomeviag);
        pviag->cidades_a_visitar = (char *) malloc(strlen(cidadesvisitadas)+1);
        strcpy(pcv->pointerviag->cidades_a_visitar, cidadesvisitadas);
        //printf("Cidades:%s\n\n",cidadesvisitadas);
        pviag->dataviagem = date;
        pviag->id = id;
    }
}

/**
 * Função print Viagens
 * @param pcv
 */
void print_viagens_dyn_array(CLASSVIAGENS_DYNARRAY pcv){
    //if (pcv.pointerviag == NULL && pcv.totalviagens == 0) printf("Nao existem viagens!!\n");
    VIAGENS *pviagem=pcv.pointerviag;
    printf("\tNumero de Viagens:%d\n", pcv.totalviagens);
        for (int i = 0; i < pcv.totalviagens; i++) {
            if(pviagem->pnomeviagem!=NULL){
            printf("Id viagem:%d\n", pcv.pointerviag->id);
            printf("Nome viagem:%s\n", pcv.pointerviag->pnomeviagem);
            printf("Id's das cidades visitadas:%s\n", pcv.pointerviag->cidades_a_visitar);
            printf("Data: %d/%d/%d\n\n", pcv.pointerviag->dataviagem.dia, pcv.pointerviag->dataviagem.mes, pcv.pointerviag->dataviagem.ano);
            pcv.pointerviag++;
            }else return;
    }
}


void edit_viagens(CLASSVIAGENS_DYNARRAY *pcv, char name[], char cidades[], DATA date){  //muda cidades e data
    VIAGENS *viag= find_viagem_nome(*pcv, name);
    VIAGENS *aux=pcv->pointerviag;
    if(viag != NULL){
        if(aux->pnomeviagem==NULL) return;  //se for null nao encontrou

        aux->pnomeviagem=(char *) malloc(strlen(name) + 1);
        strcpy(aux->pnomeviagem, name);
        aux->cidades_a_visitar=(char*) malloc(strlen(cidades)+1);
        strcpy(aux->cidades_a_visitar,cidades);
        aux->dataviagem=date;
    }
}


VIAGENS * find_viagem_nome(CLASSVIAGENS_DYNARRAY cv, char name[]){
    VIAGENS *pv = cv.pointerviag;
    for(int i = 0; i< cv.totalviagens; i++){
        if(strcmp((pv->pnomeviagem + i), name) == 0){
            return pv;
        }
        pv++;
    }
    return NULL;
}

VIAGENS * find_viagem_id(CLASSVIAGENS_DYNARRAY cv, int id){
    VIAGENS *pv = cv.pointerviag;
    for(int i = 0; i< cv.totalviagens; i++){
        if(pv->id==id){
            return pv;
        }
        pv++;
    }
    return NULL;
}

void remove_viagem_byid(CLASSVIAGENS_DYNARRAY *pcv, int id) {
    VIAGENS *pv = find_viagem_id(*pcv, id);
    VIAGENS *aux=pcv->pointerviag;
    if (pv != NULL) {   //existe uma viagem

        if(aux==pcv->pointerviag+pcv->totalviagens-1){  //se for ultimo mete tudo a null e da return
            aux->pnomeviagem=NULL;
            aux->cidades_a_visitar=NULL;
            aux->dataviagem.dia=0,aux->dataviagem.mes=0,aux->dataviagem.ano=0;
            aux->id=0;
            return;
        }

        //se estiver no meio ou no inicio
        VIAGENS *viag_seguinte=aux+1;   //viag seguinte
        for ( int i =0 ; i <pcv->totalviagens; i++) { //comeca no meio e vai ate ao fim
            aux=aux+1;
            aux->pnomeviagem=viag_seguinte->pnomeviagem;
            aux->cidades_a_visitar=viag_seguinte->cidades_a_visitar;
            aux->dataviagem=viag_seguinte->dataviagem;
            aux->id=viag_seguinte->id;
            aux++;
            viag_seguinte++;
        }
        pcv->totalviagens--;
    }
}



void free_dynarray_classviagens(CLASSVIAGENS_DYNARRAY *pcv){
    VIAGENS *pv = pcv->pointerviag;
    if(pv==NULL){
        printf("Nao existem viagens para libertar!!\n");
        return;
    }
    for (int i = 0; i < pcv->totalviagens; ++i) {
        free(pv->pnomeviagem);
    }
    free(pcv->pointerviag);
}


void save_viagens_txt(CLASSVIAGENS_DYNARRAY pcv, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"w");
    if(fp==NULL){
        printf("ERROR!\n");
        return;
    }
    fprintf(stdout, "save_cidades_txt(%s): saving cidades...\n", filename);

    VIAGENS *new=pcv.pointerviag;
    fprintf(fp, "Numero de Viagens: %d \n", pcv.totalviagens);
    for (int i = 0; i < pcv.totalviagens; i++) {
        fprintf(fp, "Id: %d, Nome: %s, Cidades visitadas: %s, Data: %d/%d/%d\n",new->id,new->pnomeviagem,new->cidades_a_visitar,new->dataviagem.dia,new->dataviagem.mes,new->dataviagem.ano);
        new++;
    }
    fprintf(stdout, "save_cidades_txt(%s): file closed.\n", filename);
    fclose(fp);
}

void read_viagens_txt(CLASSVIAGENS_DYNARRAY *pcs, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("ERROR!! %s\n",filename);
        return;
    }
    fprintf(stdout, "read_viagens_txt(%s): reading viagens...\n", filename);

    int id;
    char lixo[50],nome[50],cidades[50];
    DATA date;
    int size=2;

    //Create dyn array (está vazio)
    create_dynarray_classviagens(pcs,size);
    // Numero de Viagens: %d
    fscanf(fp,"%[^:] %*[:] %d",lixo,&size);
    for(int i=0;i<size;i++){
        // Line format: "Id: %d, Nome: %s, Cidades visitadas: %s, Data: %d/%d/%d"
        // %*s limpa tudo ate ao primeiro espaco
        // i)   read until ':' (everything not ':') -> %[^:]
        // ii)  ignore ':'                          -> %*[:]
        // %[^:] %*[:] read and ignore == lixo
        fscanf(fp,"%[^:] %*[:] %d %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %d %*[/] %d %*[/] %d",
               lixo,&id,lixo,nome,lixo,cidades,lixo,&date.dia,&date.mes,&date.ano);
        insert_viagens_dyn_array(pcs,nome,cidades,date,id);

    }

    fprintf(stdout, "read_dyn_array_rects_txt(%s): file closed.\n", filename);
    fclose(fp);
}

void save_viagens_bin(CLASSVIAGENS_DYNARRAY pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"wb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    fwrite(&pcs.totalviagens,sizeof(int),1,fp);
    VIAGENS *viag=pcs.pointerviag;
    for(int i=0;i<pcs.totalviagens;i++) {
        int size_nome= strlen(viag->pnomeviagem) + 1;// tamanho de pnomeviagem  +1
        fwrite(&size_nome, sizeof(int), 1, fp);   // tamanho de pnomeviagem
        fwrite(pcs.pointerviag->pnomeviagem, sizeof(char), size_nome, fp);//escreve pnomeviagem
        fwrite(&(viag->id), sizeof(int), 1, fp);//escrece ID
        int size= strlen(viag->cidades_a_visitar) + 1;// tamanho de descricao  +1
        fwrite(&size,sizeof(char),1,fp);//ler tamanho cidades[]
        fwrite((viag->cidades_a_visitar), sizeof(char), size, fp);//escreve cidades
        fwrite(&(viag->dataviagem.dia), sizeof(float),1,fp); //dia
        fwrite(&(viag->dataviagem.mes), sizeof(float),1,fp); //mes
        fwrite(&(viag->dataviagem.ano), sizeof(float),1,fp); //ano

    }
    fclose(fp);
}


void read_viagens_bin(CLASSVIAGENS_DYNARRAY *pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"rb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    int total_viagens=0,id=0,size_nome=0,size=0;
    char nome_viagem[50],cidades[50];
    DATA date;

    fread(&total_viagens,sizeof(int),1,fp);
    for (int i = 0; i < total_viagens; i++) {
        fread(&size_nome,sizeof(int),1,fp);//ler tamanho pnomeviagem
        fread(nome_viagem,sizeof(char),size_nome,fp);//ler pnomeviagem
        fread(&id,sizeof(int),1,fp);//le id
        fread(&size,sizeof(char),1,fp);
        fread(cidades,sizeof(char),size,fp);
        fread(&date.dia,sizeof(float),1,fp);//
        fread(&date.mes,sizeof(float),1,fp);//
        fread(&date.ano,sizeof(float),1,fp);//
        insert_viagens_dyn_array(pcs,nome_viagem,cidades,date,id);
    }
    fclose(fp);
}