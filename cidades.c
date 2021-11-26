#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Cidades        ////////////////////////////////////////////////
char ficheiro_cidades[]="cidades.txt";

void insert_cidades_ordered(CLASSCIDADES *pcs,int id,char name[],char desc[],float latitude,float longitude,Pol pontosInt[]){

    CIDADES *new=(CIDADES*)malloc(sizeof(CIDADES));
    new->ID=id;
    new->nome=(char*)malloc(sizeof(char));
    strcpy(new->nome,name);
    new->descricao=(char*)malloc(sizeof(char));
    strcpy(new->descricao,desc);
    new->coordenadas.x=latitude;
    /*new->coordenadas.y=longitude;
    new->pontosInteresse=(Pol*)malloc(sizeof(Pol));
    strcpy(new->pontosInteresse,pontosInt); */
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
    if (cid == NULL && pcs.totalcidades==0){     //não existem cidades
        //printf("Numero de cidades:%d\n", pcs.totalcidades);
        printf("Nao existem cidades inseridas!!\n\n");
    }
    else {                                                  //print dados cidade
        printf("\tNumero de cidades:%d\n", pcs.totalcidades);
        while (cid != NULL) {
            printf("Id:%d\n", cid->ID);
            printf("Nome cidade:%s\n", cid->nome);
            printf("Descricao:%s\n",cid->descricao);
            printf("[Coordenadas]Latitude: %f Longitude: %f\n",cid->coordenadas.x,cid->coordenadas.y);
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


void save_cidades_bin(CLASSCIDADES pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"wb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    fwrite(&pcs.totalcidades,sizeof(int),1,fp);
    CIDADES *cid=pcs.pointercid;
    for(int i=0;i<pcs.totalcidades;i++) {
        int size_nome=strlen(cid->nome)+1;// tamanho de nome  +1
        fwrite(&size_nome, sizeof(int), 1, fp);   // tamanho de nome
        fwrite(cid->nome, sizeof(char), size_nome, fp);//escreve nome
        fwrite(&(cid->ID), sizeof(int), 1, fp);//escrece ID
        int size=strlen(cid->descricao)+1;// tamanho de descricao  +1
        fwrite(&size,sizeof(char),1,fp);//ler tamanho descricao
        fwrite((cid->descricao), sizeof(char), size, fp);//escreve descricao
        fwrite(&(cid->coordenadas.x), sizeof(float),1,fp); //latitude
        fwrite(&(cid->coordenadas.y), sizeof(float),1,fp); //longitude
        fwrite((cid->pontosInteresse), sizeof(char),size,fp);    //Lista pontos interesse
        cid=cid->pnext;
    }
    fclose(fp);
}


void read_cidades_bin(CLASSCIDADES *pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"rb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    int total_cidades=0,id_cidade=0,size_nome=0,size=0;
    float latitude=0.0f,longitude=0.0f;
    char nome_cidade[100];
    char descricao_cliente[50];
    char lista_pontos[50];
    fread(&total_cidades,sizeof(int),1,fp);
    for (int i = 0; i < total_cidades; i++) {
        fread(&size_nome,sizeof(int),1,fp);//ler tamanho nome
        fread(nome_cidade,sizeof(char),size_nome,fp);//ler nome
        fread(&id_cidade,sizeof(int),1,fp);//le id cidade
        fread(&size,sizeof(char),1,fp);//ler tamanho descricao
        fread(descricao_cliente,sizeof(char),size,fp);//le descricao cidade
        fread(&latitude,sizeof(float),1,fp);//le latitude cidade
        fread(&longitude,sizeof(float),1,fp);//le longitude cidade
        fread(lista_pontos,sizeof(char),size,fp);//le lista pontos interesse cidade
        insert_cidades_ordered(pcs,id_cidade,nome_cidade,descricao_cliente,latitude,longitude,lista_pontos);
    }
    fclose(fp);
}


