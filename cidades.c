#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Cidades        ////////////////////////////////////////////////
char ficheiro_cidades[]="cidades.txt";

void insert_cidades_ordered(CLASSCIDADES *pcs,int id,int name,char desc,float latitude,float longitude,char pontosInt[]){

    CIDADES *new=(CIDADES*) malloc(sizeof(CIDADES));
    new->nome=(char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(new->nome,name);
    new->ID=id;
    new->coordenadas.x=latitude;
    new->coordenadas.y=longitude;
    new->pontosInteresse=(char*)malloc(sizeof(char));
    strcpy(new->pontosInteresse,pontosInt);
    new->pnext=NULL;


    //case1 First
    if(pcs->pointercid==NULL||pcs->totalcidades==0){
        pcs->pointercid=new;
        pcs->totalcidades++;
        return;
    }

    //case2 head
    CIDADES *pcurrent=pcs->pointercid,*pand=NULL;
    while(pcurrent!=NULL && strcmp(name,pcurrent->nome)>0){
        pand=pcurrent;
        pcurrent=pcurrent->pnext;
    }
    if(pcurrent==pcs->pointercid){ //caso o ciclo while nao tenha andado, o pcurrent está na primeira posicao
        new->pnext=pcurrent;
        pcs->pointercid=new;
        pcs->totalcidades++;
        return;
    }
    //head e tail no mesmo
    pand->pnext=new;
    new->pnext=pcurrent;
    pcs->totalcidades++;
///////////////////////////////

    //case3 tail

    if(pcurrent==NULL){
        pand->pnext=new;
        return;
    }
}

void edit_cidades(CLASSCIDADES *pcs,int id,int novonome,char novadesc,float x,float y,char pontos[]){

        CIDADES *cid= find_cidade_nome(*pcs,pcs->pointercid->nome);
        cid->nome=novonome;
        cid->ID=id;
        cid->descricao=novadesc;
        cid->coordenadas.x=x;
        cid->coordenadas.y=y;
        cid->pontosInteresse=pontos;
}

CIDADES * find_cidade_nome(CLASSCIDADES pcs,char nome[]){
    CIDADES *cid=pcs.pointercid;
    while (cid!=NULL){
        if (strcmp(cid->nome,nome)==0){
            return cid;
        }
        cid=cid->pnext;
    }
    return NULL;
}

CIDADES * find_cidade_ID(CLASSCIDADES pcs, int id){
    CIDADES *cid=pcs.pointercid;

    while (cid!=NULL){
        if (cid->ID==id){
            return cid;
        }
        cid=cid->pnext;
    }
    return NULL;
}

CIDADES * edit_descricao_cidade(CLASSCIDADES *pcs,char newdesc){

    CIDADES *cid= find_cidade_ID(*pcs,pcs->pointercid->ID);
    while (cid!=NULL){
            cid->descricao=newdesc;
            return cid;
        }
        //pcs->pointercid=pcs->pointercid->pnext;
    return NULL;
}

void remove_cidades_nome(CLASSCIDADES *pcs,char nome[]){

        if (pcs->pointercid== NULL) { // Empty
            return;
        }
        CIDADES *pant = NULL, *pcurrent = pcs->pointercid;
        while (pcurrent != NULL && strcmp(pcurrent->nome,nome) != 0) {
            pant = pcurrent;
            pcurrent = pcurrent->pnext;
        }
        if (pcurrent == NULL) {
            return;
        }
        if(pcs->pointercid == pcurrent){
            pcs->pointercid = pcurrent->pnext;
            pcs->totalcidades--;
            free(pcurrent);
            return;
        }
        pant->pnext = pcurrent->pnext; // Middle/Tail
        free(pcurrent);
        pcs->totalcidades--;
}

void print_cidades(CLASSCIDADES pcs){
    CIDADES *cid=pcs.pointercid;
    if (pcs.pointercid == NULL && pcs.totalcidades==0){     //não existem cidades
        printf("Nao existem cidades inseridas!!\n");
    }
    else {                                                  //print dados cidade
        //printf("\tNumero de cidades:%d\n", pcs.totalcidades);
        while (cid != NULL) {
            printf("Nome cidade:%s\n", cid->nome);
            printf("Id:%d\n", cid->ID);
            printf("Descricao:%s\n",cid->descricao);
            printf("Coordenadas: %f %f\n",cid->coordenadas.x,cid->coordenadas.y);
            printf("Pontos de Interesse:%s\n",cid->pontosInteresse);
            cid=cid->pnext;
        }
    }
}

void save_cidades_txt(CLASSCIDADES pcs, char filename[]){
    FILE *fp=NULL;

    fp=fopen(filename, "w");

    if(fp!=NULL) {
        CIDADES *new=pcs.pointercid;
        fprintf(fp, "Numero de Cidades: %d \n", pcs.totalcidades);
        while (new!=NULL){
            fprintf(fp,"ID: %d, Nome: %s, Descricao: %s, Latitude: %d, Longitude: %d, Lista de Pontos Interesse: %s\n",new->ID,new->nome,new->descricao,new->coordenadas.x, new->coordenadas.y,new->pontosInteresse->pontos);
            new=new->pnext;
        }
        fclose(fp);
    } else{
        printf("Erro ao guardar o ficheiro!\n");
    }

}
void read_cidades_txt(CLASSCIDADES *pcs, char filename[]){
    FILE *fp=NULL;

    if((fp=fopen(filename, "r"))==NULL){
        printf("Erro ao abrir ficheiro edificio\n");
        return;
    }
    int n_cidades,id_cidade,descricao,latitude,longitude;
    char nome[50],pontos[50];
    char lixo[50];
    // %*s limpa tudo ate ao primeiro espaco
    // Line format: "rect 0: 0 0 1 1"
    // i)   read until ':' (everything not ':') -> %[^:]
    // ii)  ignore ':'                          -> %*[:]
    //...
    fscanf(fp,"%[^:] %*[:] %d",lixo,&n_cidades);
    for (int i = 0; i <n_cidades ; i++) {
        fscanf(fp,"%[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %d %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %d %[^:] %*[:] %d %[^:] %*[:] %[^,] %*[,]",lixo,nome,lixo,&id_cidade,lixo,descricao,lixo,&latitude,lixo,&longitude,lixo,&pontos);
        insert_cidades_ordered(pcs,id_cidade,nome,descricao,latitude,longitude,pontos);
    }
    fclose(fp);
}
void save_cidades_bin(CLASSCIDADES pcs, char filename[]);
void read_cidades_bin(CLASSCIDADES *pcs, char filename[]);



