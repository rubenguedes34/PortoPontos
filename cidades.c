#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Cidades        ////////////////////////////////////////////////

void create_dynarray_classcidades(CLASSCIDADES_DYNARRAY *pcc, int initsize){
    CIDADES *pcid=(CIDADES *)calloc(initsize, sizeof(CIDADES));
    pcc->pointercid=pcid;
    pcc->totalcidades=initsize;
    //printf("Dyn array created!");
}

void insert_cidade_dynarray(CLASSCIDADES_DYNARRAY *pcc, char name[], int id, char desc[], float latitude, float longitude, char pontos[]) {
    int i = 0;
    CIDADES *pcid = pcc->pointercid;
    for (; i < pcc->totalcidades; i++) {
        if (pcid->pnomecidade == NULL) {
            //printf("Insercao direta!\n");
            pcid->pnomecidade = (char *) malloc(strlen(name) + 1);
            strcpy(pcid->pnomecidade, name);
            //printf("Nome:%s\n",name);
            pcid->ID=id;
            pcid->descricao=(char*)malloc(strlen(desc) + 1);
            strcpy(pcid->descricao,desc);
            //printf("Descricao:%s\n",desc);
            pcid->coordenadas.x=latitude;
            pcid->coordenadas.y=longitude;
            //printf("Coordenadas:%f %f\n",latitude,longitude);
            pcid->pontosInt= (char *) malloc(strlen(pontos) + 1);
            strcpy(pcid->pontosInt, pontos);
            //printf("Pontos:%s\n\n", pontos);
            return;
        }
        pcid++;
    }
    if (i == pcc->totalcidades) {
        int oldsize = pcc->totalcidades;
        int newsize = oldsize + 5;
        pcc->pointercid=(CIDADES *)realloc(pcc->pointercid, newsize * sizeof(CIDADES));
        pcc->totalcidades=newsize;
        pcid = pcc->pointercid + oldsize;
        for (i = oldsize; i < newsize; i++){
            pcid->pnomecidade = NULL;
            pcid->ID=0;
            pcid->descricao=NULL;
            pcid->coordenadas.x=0.0f,pcid->coordenadas.y=0.0f;
            pcid->pontosInt=NULL;
            pcid++;
        }
        pcid=pcc->pointercid+oldsize;
        pcid->pnomecidade = (char *) malloc(strlen(name) + 1);
        strcpy(pcid->pnomecidade, name);
        //printf("Nome:%s\n",name);
        pcid->ID=id;
        pcid->descricao=(char*)malloc(strlen(desc) + 1);
        strcpy(pcid->descricao,desc);
        //printf("Descricao:%s\n",desc);
        pcid->coordenadas.x=latitude;
        pcid->coordenadas.y=longitude;
        //printf("Coordenadas:%f %f\n",latitude,longitude);
        pcid->pontosInt= (char *) malloc(strlen(pontos) + 1);
        strcpy(pcid->pontosInt, pontos);
        //printf("Pontos:%s\n\n", pontos);
    }
}

void print_dynarray_classcidades(CLASSCIDADES_DYNARRAY pcc) {
    //if (pcc.pointercid == NULL && pcc.totalcidades == 0) printf("Nao existem cidades!!\n");
    CIDADES *pcid=pcc.pointercid;
    printf("\tNumero de cidades:%d\n", pcc.totalcidades);
        for(int i = 0; i < pcc.totalcidades; i++){
            if(pcid->pnomecidade != NULL){      //existe cid
            printf("ID:%d\n", pcc.pointercid->ID);
            printf("Nome:%s\n", pcc.pointercid->pnomecidade);
            printf("Descricao:%s\n", pcc.pointercid->descricao);
            printf("Latitude:%0.2f\n", pcc.pointercid->coordenadas.x);
            printf("Longitude:%0.2f\n", pcc.pointercid->coordenadas.y);
            printf("Lista Pontos Interesse:%s\n\n", pcc.pointercid->pontosInt);
            pcc.pointercid++;
            } else return;
    }
}

CIDADES * find_cidade_nome(CLASSCIDADES_DYNARRAY pcs, char nome[]){
    CIDADES *cid=pcs.pointercid;
    for (int i = 0; i < pcs.totalcidades ; ++i) {
        if (strcmp(pcs.pointercid->pnomecidade, nome) == 0) {
            return cid;
        }
        cid++;
    }
    return NULL;
}

CIDADES * find_cidade_ID(CLASSCIDADES_DYNARRAY pcs, int id){
    CIDADES *cid=pcs.pointercid;
    for (int i = 0; i < pcs.totalcidades ; ++i) {
        if (cid->ID==id){
            return cid;
        }
        cid++;
    }
    return NULL;
}

void edit_cidades(CLASSCIDADES_DYNARRAY *pcc, char nome[], char novadesc[], float x, float y, char pontos[]) {

    CIDADES *cid = find_cidade_nome(*pcc, nome);
    CIDADES *aux = pcc->pointercid;
    if (cid != NULL) {
        if (aux->pnomecidade == NULL) return;  //se for null nao encontrou

        aux->pnomecidade=(char*) malloc(strlen(nome)+1);
        strcpy(aux->pnomecidade, nome);
        aux->descricao=(char*) malloc(strlen(novadesc)+1);
        strcpy(aux->descricao, novadesc);
        aux->coordenadas.x = x;
        aux->coordenadas.y = y;
        aux->pontosInt=(char*) malloc(strlen(pontos)+1);
        strcpy(aux->pontosInt, pontos);
    }
}


/*CIDADES * edit_descricao_cidade(CLASSCIDADES_DYNARRAY *pcs, char *newdesc){
    CIDADES *cid= find_cidade_ID(*pcs,pcs->pointercid->ID);
    while (pcs->pointercid != NULL){
            cid->descricao=newdesc;
            return cid;
        }
    return NULL;
} */

void remove_cidade_id(CLASSCIDADES_DYNARRAY *pcs, int id){


}

void free_dynarray_classcidades(CLASSCIDADES_DYNARRAY *pcs){
    CIDADES *pcid = pcs->pointercid;
    if(pcid==NULL){
        printf("Nao existem cidades para libertar\n");
        return;
    }
    for (int i = 0; i < pcs->totalcidades; ++i) {
        free(pcid->pnomecidade);
    }
    free(pcs->pointercid);
}


void save_cidades_txt(CLASSCIDADES_DYNARRAY pcs, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"w");
    if(fp==NULL){
        printf("ERROR!\n");
        return;
    }
    fprintf(stdout, "save_cidades_txt(%s): saving cidades...\n", filename);

    CIDADES *new=pcs.pointercid;
    fprintf(fp, "Numero de Cidades: %d \n", pcs.totalcidades);
    for (int i = 0; i < pcs.totalcidades; i++) {
        fprintf(fp, "ID: %d, Nome: %s, Descricao: %s, Latitude: %f, Longitude: %f, Lista de Pontos Interesse: %s\n", new->ID, new->pnomecidade, new->descricao, new->coordenadas.x, new->coordenadas.y, new->pontosInt);
        new++;
    }
    fprintf(stdout, "save_cidades_txt(%s): file closed.\n", filename);
    fclose(fp);
}


void read_cidades_txt(CLASSCIDADES_DYNARRAY *pcs, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("ERROR!! %s\n",filename);
        return;
    }
    fprintf(stdout, "read_cidades_txt(%s): reading cidades...\n", filename);

    int id_cidade;
    float latitude,longitude;
    char lixo[50],nome[50],descricao[50],pontos[50];
    int size=2;

    //Create dyn array (está vazio)
    create_dynarray_classcidades(pcs,size);
    // Numero de Cidades: %d
    fscanf(fp,"%[^:] %*[:] %d",lixo,&size);
    for (int i = 0; i <size ; i++) {
        // ID: 1, Nome: Cidade1, Descricao: %s, Latitude: 2.0, Longitude: 2.0, Lista de Pontos Interesse: %s
        // i)   read until ':' (everything not ':') -> %[^:]
        // ii)  ignore ':'                          -> %*[:]
        // %[^:] %*[:] read and ignore == lixo
        // lixo + %s + ',' == %[^:] %*[:] %[^,] %*[,]
        fscanf(fp,"%[^:] %*[:] %d %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %f %[^:] %*[:] %f %[^:] %*[:] %[^,] %*[,]",
               lixo,&id_cidade,lixo,nome,lixo,descricao,lixo,&latitude,lixo,&longitude,lixo,pontos);
        insert_cidade_dynarray(pcs,nome,id_cidade,descricao,latitude,longitude,pontos);

    }

    fprintf(stdout, "read_cidades_txt(%s): file closed.\n", filename);
    fclose(fp);
}


void save_cidades_bin(CLASSCIDADES_DYNARRAY pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"wb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }
    fwrite(&pcs.totalcidades,sizeof(int),1,fp);
    CIDADES *cid=pcs.pointercid;
    for(int i=0;i<pcs.totalcidades;i++) {
        int size_nome= strlen(cid->pnomecidade) + 1;// tamanho de pnomeviagem  +1
        fwrite(&size_nome, sizeof(int), 1, fp);   // tamanho de pnomeviagem
        fwrite(pcs.pointercid->pnomecidade, sizeof(char), size_nome, fp);//escreve pnomeviagem
        fwrite(&(cid->ID), sizeof(int), 1, fp);//escrece ID
        int size=strlen(cid->descricao)+1;// tamanho de descricao  +1
        fwrite(&size,sizeof(char),1,fp);//ler tamanho descricao
        fwrite((cid->descricao), sizeof(char), size, fp);//escreve descricao
        fwrite(&(cid->coordenadas.x), sizeof(float),1,fp); //latitude
        fwrite(&(cid->coordenadas.y), sizeof(float),1,fp); //longitude
        fwrite((cid->pontosInt), sizeof(char), size, fp);    //Lista pontosInt interesse
    }
    fclose(fp);
}


void read_cidades_bin(CLASSCIDADES_DYNARRAY *pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"rb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    int total_cidades=0,id_cidade=0,size_nome=0,size=0;
    float latitude=0.0f,longitude=0.0f;
    char nome_cidade[100];
    char descricao[50];
    char lista_pontos[50];
    fread(&total_cidades,sizeof(int),1,fp);
    for (int i = 0; i < total_cidades; i++) {
        fread(&size_nome,sizeof(int),1,fp);//ler tamanho pnomeviagem
        fread(nome_cidade,sizeof(char),size_nome,fp);//ler pnomeviagem
        fread(&id_cidade,sizeof(int),1,fp);//le id cidade
        fread(&size,sizeof(char),1,fp);//ler tamanho descricao
        fread(descricao,sizeof(char),size,fp);//le descricao cidade
        fread(&latitude,sizeof(float),1,fp);//le latitude cidade
        fread(&longitude,sizeof(float),1,fp);//le longitude cidade
        fread(lista_pontos,sizeof(char),size,fp);//le lista pontosInt interesse cidade
        insert_cidade_dynarray(pcs,nome_cidade,id_cidade,descricao,latitude,longitude,lista_pontos);
    }
    fclose(fp);
}


