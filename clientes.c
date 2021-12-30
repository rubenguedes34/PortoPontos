#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Clientes        ////////////////////////////////////////////////
char ficheiro_clientes[]="clientes.txt";

/**
 * Função inserir cliente
 * @param pcs
 * @param name
 * @param id
 */
void insert_cliente_ordered(CLASSCLIENTE *pcs, char name[], int id, int NIF, char email[]) {
    //Consider the 4 possibilities: Queue is empty, insert head, insert tail, insert in the middle
    CLIENTE *new = (CLIENTE *) malloc(sizeof(CLIENTE));
    new->id = id;
    new->nome = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new->nome, name);
    new->NIF = NIF;
    new->email = (char *) malloc(sizeof(char) * (strlen(email)) + 1);
    strcpy(new->email, email);
    new->pnext = NULL;

    //1st case, Empty List
    if (pcs->pointerc == NULL || pcs->totalclientes == 0) {
        pcs->pointerc = new;
        pcs->totalclientes++;
        return;
    }

    //2nd case, Head + Tail + Middle with if's to check which is what
    CLIENTE *pcurrent = pcs->pointerc, *pand = NULL;
    while (pcurrent != NULL && strcmp(name, pcurrent->nome) > 0) {
        pand = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == pcs->pointerc) {      // Head insertion
        //printf("Inserindo na head\n");
        new->pnext = pcurrent;
        pcs->pointerc = new;
        pcs->totalclientes++;
        return;
    }
    if (pcurrent == NULL) {           // Tail insertion
        // é o ultimo pois aponta para NULL
        //printf("Inserindo na tail\n");
        pand->pnext = new;
        pcs->totalclientes++;
        return;
    }                              // Middle
    //printf("Inserindo no middle\n");
    new->pnext = pcurrent;
    pand->pnext = new;
    pcs->totalclientes++;

}

/**
 * Função printar Clientes
 * @param pcs
 */
void print_cliente(CLASSCLIENTE pcs){
    CLIENTE *pcurrent=pcs.pointerc;
    printf("\tNumero de clientes:%d\n",pcs.totalclientes);
    while (pcurrent!=NULL){
        printf("Nome:%s\n",pcurrent->nome);
        printf("Id:%d\n",pcurrent->id);
        printf("NIF:%d\n",pcurrent->NIF);
        printf("Email:%s\n\n",pcurrent->email);
        pcurrent=pcurrent->pnext;
    }
}

/**
 * Função remover clientes
 * @param pcs
 * @param name
 */
void remove_cliente_byname(CLASSCLIENTE *pcs, char name[]){    //Ordered
    if (pcs->pointerc == NULL) { // Empty
        return;
    }
    CLIENTE *pant = NULL, *pcurrent = pcs->pointerc;
    while (pcurrent != NULL && strcmp(pcurrent->nome, name) != 0) {
        pant = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == NULL) {
        return;
    }
    if(pcs->pointerc == pcurrent){
        pcs->pointerc = pcurrent->pnext;
        pcs->totalclientes--;
        free(pcurrent);
        return;
    }
    pant->pnext = pcurrent->pnext; // Middle/Tail
    free(pcurrent);
    pcs->totalclientes--;
}

/**
 * Função procurar cliente pelo id
 * @param psnp
 * @param id
 * @return
 */
CLIENTE *find_cliente_id(CLASSCLIENTE *pcs, int id) {
    CLIENTE *pcurrent = pcs->pointerc;
    while (pcurrent != NULL && pcurrent->id != id) {
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == NULL) {
        printf("\t\t\t\n|||ERROR CLIENT NOT FOUND|||\n");
    }
    return pcurrent;
}


/**
 * Função guardar clientes no ficheiro txt
 * @param pcs
 * @param filename
 */
void save_cliente_txt(CLASSCLIENTE pcs, char filename[]){
    FILE *fp=NULL;

    fp=fopen(filename, "w");

    if(fp!=NULL) {
        CLIENTE *new = pcs.pointerc;
        fprintf(fp, "Numero de Clientes: %d\n", pcs.totalclientes);
        while (new!=NULL){
            fprintf(fp, "Nome: %s id: %d NIF: %d Email: %s\n",new->nome, new->id,new->NIF,new->email);
            new=new->pnext;
        }
        fclose(fp);
    } else{
        printf("Erro ao guardar o ficheiro!\n");
    }
}

/**
 * Função ler clientes do ficheiro txt
 * @param pcs
 * @param filename
 */
void read_clientes_txt(CLASSCLIENTE *pcs, char filename[]) {
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    int totalclientes = 0;
    char nomecliente[101];
    int id,NIF;
    char email[101];
    if (fp == NULL) {
        printf("Erro ao carregar o cliente!\n");
        return;
    }

    fscanf(fp, "%*s %*s %*s %d", &totalclientes);
    for (int i = 0; i < totalclientes; i++) {
        fscanf(fp, "%*s %s %*s %d %*s %d %*s %s", nomecliente, &id,&NIF,email);
        insert_cliente_ordered(pcs,nomecliente,id,NIF,email);
    }
}

/**
 * Função guardar cliente no ficheiro binario
 * @param pcs
 * @param filename
 */
void save_cliente_bin(CLASSCLIENTE pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"wb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    fwrite(&pcs.totalclientes,sizeof(int),1,fp);
    //fwrite(&size,sizeof(int),1,fp); //guardar size
    CLIENTE *cl = pcs.pointerc;
    for(int i=0;i<pcs.totalclientes;i++) {
        int size=strlen(cl->nome)+1;// tamanho de pnomeviagem  +1
        fwrite(&size, sizeof(int), 1, fp);   // tamanho de pnomeviagem
        fwrite(cl->nome, sizeof(char), size, fp);//escreve pnomeviagem
        fwrite(&(cl->id), sizeof(int), 1, fp);//escrece id
        fwrite(&(cl->NIF), sizeof(int), 1, fp);//escreve nif
        fwrite((cl->email), sizeof(char), size + 20, fp);//escreve email
        cl=cl->pnext;
    }
    fclose(fp);
}

/**
 * Função ler cliente do ficheiro binario
 * @param pcs
 * @param filename
 */
void read_cliente_bin(CLASSCLIENTE *pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"rb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }
    int total_cliente=0,id_cliente=0,nif_cliente=0,size=0;
    char nome_cliente[100];
    char email_cliente[50];
    fread(&total_cliente,sizeof(int),1,fp);
    for (int i = 0; i < total_cliente; i++) {
        fread(&size,sizeof(int),1,fp);//ler tamanho pnomeviagem
        fread(nome_cliente,sizeof(char),size,fp);//ler pnomeviagem
        fread(&id_cliente,sizeof(int),1,fp);//le id  cliente
        fread(&nif_cliente,sizeof(int),1,fp);//le nif  cliente
        fread(email_cliente,sizeof(char),size + 20,fp);//le email  cliente
        insert_cliente_ordered(pcs,nome_cliente,id_cliente,nif_cliente,email_cliente);
    }

    fclose(fp);
}

void insert_historico(CLASSCLIENTE *pcl, int id_cliente, VIAGENS viagem_realizada[], DATA d_fim){
    CLIENTE *ccliente=pcl->pointerc;
    while (ccliente->id != id_cliente){      // ccliente not found yet
        ccliente=ccliente->pnext;
    }

    H_Clientes *hist=(H_Clientes*)malloc(sizeof(H_Clientes));
    hist->viagem=(VIAGENS*) malloc(sizeof (VIAGENS));
    //hist->data_inicio=d_inicio;
    hist->data_fim=d_fim;
    //hist->pontos=pontosInt;
    hist->pnext=NULL;

    //CLIENTE *ccliente= find_cliente_id(pcl,id_cliente);

    //1st case, Empty List
    if (ccliente->hclientes->pointerhc == NULL || ccliente->hclientes->nr_Historicos == 0) {
        ccliente->hclientes->pointerhc=hist;
        ccliente->hclientes->nr_Historicos++;
        return;
    }

    H_Clientes *ant=NULL;
    H_Clientes *atual=ccliente->hclientes->pointerhc;

    while (atual != NULL){
        ant=atual;
        atual=atual->pnext;
    }
    ant->pnext=hist;
    hist->pnext=atual;
    ccliente->hclientes->nr_Historicos++;

}

void print_historico(CLASSCLIENTE cc, int id_cliente) {
    CLIENTE *cli = find_cliente_id(&cc,id_cliente);
    H_Clientes *paux=cli->hclientes->pointerhc;
    while (paux != NULL) {
        printf("Historico do cliente: %d\n",id_cliente);
        printf("Nome da Viagem: %s\n",paux->viagem->pnomeviagem);
        printf("Cidades visitadas: %s\n",paux->viagem->cidades_a_visitar);
        printf("Data inicio da viagem: %d/%d/%d\n",paux->viagem->dataviagem.dia,paux->viagem->dataviagem.mes,paux->viagem->dataviagem.ano);
        printf("Data fim da viagem: %d/%d/%d\n",paux->data_fim.dia,paux->data_fim.mes,paux->data_fim.ano);
        //printf("Pontos Visitados: %s\n",paux->pontos);
        paux = paux->pnext;
    }
}

CLIENTE *find_historico_cidade(CLASSCLIENTE *pcs,H_Clientes hist,CIDADES cidade){

}

CLIENTE *find_historico_pol(CLASSCLIENTE *pcs,H_Clientes hist){

}