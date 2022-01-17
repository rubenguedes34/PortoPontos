#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Clientes        ////////////////////////////////////////////////

/**
 * Função inserir cliente
 * @param pcc
 * @param name
 * @param id
 *  @param nif
 *  @param email
 *  @param viagens - numero viagens para criar dyn array
 */
void insert_cliente_ordered(CLASSCLIENTE *pcc, char name[], int id, int NIF, char email[], int viagens) {

    //Consider the 4 possibilities: Queue is empty, insert head, insert tail, insert in the middle
    CLIENTE *new = (CLIENTE *) malloc(sizeof(CLIENTE));
    new->id = id;
    new->nome = (char *) malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new->nome, name);
    new->NIF = NIF;
    new->email = (char *) malloc(sizeof(char) * (strlen(email)) + 1);
    strcpy(new->email, email);
    new->viagens.n_viagens=0;
    new->pnext = NULL;
    //new->hclientes->nr_historico=0;
    //new->hclientes->pointerhc=NULL;       //not working properly, segmentation fault


    if (viagens == 2){
        create_dynarray_classviagens(new,viagens);
        new->viagens.totalviagens=viagens;
    } else{
        create_dynarray_classviagens(new,5);
        new->viagens.totalviagens=5;
    }

    //1st case, Empty List
    if (pcc->pointerc == NULL || pcc->totalclientes == 0) {
        pcc->pointerc = new;
        pcc->totalclientes++;
        return;
    }

    //2nd case, Head + Tail + Middle with if's to check which is what
    CLIENTE *pcurrent = pcc->pointerc, *pand = NULL;
    while (pcurrent != NULL && strcmp(name, pcurrent->nome) > 0) {
        pand = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == pcc->pointerc) {      // Head insertion
        //printf("Inserindo na head\n");
        new->pnext = pcurrent;
        pcc->pointerc = new;
        pcc->totalclientes++;
        return;
    }
    if (pcurrent == NULL) {           // Tail insertion
        // é o ultimo pois aponta para NULL
        //printf("Inserindo na tail\n");
        pand->pnext = new;
        pcc->totalclientes++;
        return;
    }                              // Middle
    //printf("Inserindo no middle\n");
    new->pnext = pcurrent;
    pand->pnext = new;
    pcc->totalclientes++;

}

/**
 * Função printar Clientes
 * @param pcc
 */
void print_cliente(CLASSCLIENTE pcc){
    CLIENTE *pcurrent=pcc.pointerc;
    printf("\tNumero de clientes:%d\n", pcc.totalclientes);
    while (pcurrent!=NULL){
        printf("Nome:%s\n",pcurrent->nome);
        printf("Id:%d\n",pcurrent->id);
        printf("NIF:%d\n",pcurrent->NIF);
        printf("Email:%s\n\n",pcurrent->email);
        //printf("Numero viagens realizadas:%d\n\n",pcurrent->viagens.totalviagens);
        pcurrent=pcurrent->pnext;
    }
}

/**
 * Função editar clientes
 * @param pcl
 * @param novonome
 * @param id
 */
void edit_cliente(CLASSCLIENTE *pcl, int id, char novonome[], int new_nif, char new_email[]){
   CLIENTE *cliente=pcl->pointerc;

    while (cliente->id != id){
        cliente=cliente->pnext;
    }
    strcpy(cliente->nome, novonome);
    cliente->NIF=new_nif;
    strcpy(cliente->email, new_email);

}


/**
 * Função remover clientes
 * @param pcc
 * @param name
 */
void remove_cliente_byname(CLASSCLIENTE *pcc, char name[]){    //Ordered
    if (pcc->pointerc == NULL) { // Empty
        return;
    }
    CLIENTE *pant = NULL, *pcurrent = pcc->pointerc;
    while (pcurrent != NULL && strcmp(pcurrent->nome, name) != 0) {
        pant = pcurrent;
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == NULL) {
        return;
    }
    if(pcc->pointerc == pcurrent){
        pcc->pointerc = pcurrent->pnext;
        pcc->totalclientes--;
        free(pcurrent);
        return;
    }
    pant->pnext = pcurrent->pnext; // Middle/Tail
    free(pcurrent);
    pcc->totalclientes--;
}

/**
 * Função procurar cliente pelo NIF
 * @param pcc
 * @param NIF
 * @return
 */
CLIENTE *find_cliente_nif(CLASSCLIENTE *pcc, int NIF ){
    CLIENTE *pcurrent = pcc->pointerc;
    while (pcurrent != NULL && pcurrent->id != NIF) {
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == NULL) {
        printf("\t\t\t\n|||ERROR CLIENT NOT FOUND|||\n");
    }
    return pcurrent;
}


/**
 * Função procurar cliente pelo nome
 * @param pcc
 * @param nome
 * @return
 */
CLIENTE *find_cliente_nome(CLASSCLIENTE *pcc,char nome[]) {
    CLIENTE *pcurrent = pcc->pointerc;
    while (pcurrent != NULL && strcmp(pcurrent->nome,nome) != 0) {
        pcurrent = pcurrent->pnext;
    }
    if (pcurrent == NULL) {
        printf("\t\t\t\n|||ERROR CLIENT NOT FOUND|||\n");
    }
    return pcurrent;
}

void sort_numbers_ascending(int number[], int count) {
    int temp, i, j, k;
    for (j = 0; j < count; ++j) {
        for (k = j + 1; k < count; ++k) {
            if (number[j] > number[k]) {
                temp = number[j];
                number[j] = number[k];
                number[k] = temp;
            }
        }
    }
    printf("Numbers in ascending order:\n");
    for (i = 0; i < count; ++i)
        printf("%d\n", number[i]);
}


void print_clientes_orderByNif(CLASSCLIENTE cc){

    CLIENTE *pcurrent=cc.pointerc;
    CLIENTE *next=NULL;
    printf("\tNumero de clientes:%d\n", cc.totalclientes);

    if(pcurrent==NULL)return;       //correct order- 3 2 1
    else {
        while (pcurrent != NULL) {
            next = pcurrent->pnext;
            while (next != NULL) {
                if (pcurrent->NIF < next->NIF) {
                    printf("Nome:%s\n", pcurrent->nome);
                    printf("Id:%d\n", pcurrent->id);
                    printf("NIF:%d\n", pcurrent->NIF);
                    printf("Email:%s\n\n", pcurrent->email);
                }
                next = next->pnext;
            }
            if (pcurrent->id != cc.totalclientes) pcurrent = pcurrent->pnext;

            }
        }
}



/**
 * Função guardar clientes no ficheiro txt
 * @param pcl
 * @param filename
 */
void save_cliente_txt(CLASSCLIENTE pcl, char filename[]){
    FILE *fp=NULL;

    fp=fopen(filename, "w");

    if(fp!=NULL) {
        CLIENTE *new = pcl.pointerc;
        fprintf(fp, "Numero de Clientes: %d\n", pcl.totalclientes);
        while (new!=NULL){
            fprintf(fp, "Nome: %s id: %d NIF: %d Email: %s %d\n",new->nome, new->id,new->NIF,new->email,new->viagens.totalviagens);
            new=new->pnext;
        }
        fclose(fp);
    } else{
        printf("Erro ao guardar o ficheiro!\n");
    }
}

/**
 * Função ler clientes do ficheiro txt
 * @param pcl
 * @param filename
 */
void read_clientes_txt(CLASSCLIENTE *pcl, char filename[]) {
    FILE *fp = NULL;
    fp = fopen(filename, "r");
    int totalclientes = 0;
    char nomecliente[101];
    int id,NIF,viagens=0;
    char email[101];
    if (fp == NULL) {
        printf("Erro ao carregar o cliente!\n");
        return;
    }

    fscanf(fp, "%*s %*s %*s %d", &totalclientes);
    for (int i = 0; i < totalclientes; i++) {
        fscanf(fp, "%*s %s %*s %d %*s %d %*s %s %*s %d", nomecliente, &id,&NIF,email,&viagens);
        insert_cliente_ordered(pcl, nomecliente, id, NIF, email, viagens);
    }
}

/**
 * Função guardar cliente no ficheiro binario
 * @param pcl
 * @param filename
 */
void save_cliente_bin(CLASSCLIENTE pcl, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"wb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    fwrite(&pcl.totalclientes, sizeof(int), 1, fp);
    //fwrite(&size,sizeof(int),1,fp); //guardar size
    CLIENTE *cl = pcl.pointerc;
    for(int i=0; i < pcl.totalclientes; i++) {
        int size=strlen(cl->nome)+1;// tamanho +1
        fwrite(&size, sizeof(int), 1, fp);   // tamanho
        fwrite(cl->nome, sizeof(char), size, fp);//escreve
        fwrite(&(cl->id), sizeof(int), 1, fp);//escrece id
        fwrite(&(cl->NIF), sizeof(int), 1, fp);//escreve nif
        fwrite((cl->email), sizeof(char), size + 20, fp);//escreve email
        fwrite(&cl->viagens.totalviagens,sizeof(int),1,fp);
        cl=cl->pnext;
    }

    fprintf(stdout, "save_clientes_bin(%s): file closed.\n", filename);
    fclose(fp);
}

/**
 * Função ler cliente do ficheiro binario
 * @param pcl
 * @param filename
 */
void read_cliente_bin(CLASSCLIENTE *pcl, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"rb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }
    int total_cliente=0,id_cliente=0,nif_cliente=0,viagens=0,size=0;
    char nome_cliente[100];
    char email_cliente[50];
    fread(&total_cliente,sizeof(int),1,fp);
    for (int i = 0; i < total_cliente; i++) {
        fread(&size,sizeof(int),1,fp);//ler tamanho nomeviagem
        fread(nome_cliente,sizeof(char),size,fp);//ler nomeviagem
        fread(&id_cliente,sizeof(int),1,fp);//le id  cliente
        fread(&nif_cliente,sizeof(int),1,fp);//le nif  cliente
        fread(email_cliente,sizeof(char),size + 20,fp);//le email  cliente
        fread(&viagens,sizeof(int),1,fp);
        insert_cliente_ordered(pcl, nome_cliente, id_cliente, nif_cliente, email_cliente, viagens);
    }

    fclose(fp);
}


/**
 * Função inserir historico de cliente numa viagem
 * @param pcc
 * @param id_cliente
 * @param nome_viagem
 *  @param d_inicio
 *  @param d_fim
 */
void insert_historico(CLASSCLIENTE *pcc, int id_cliente, char nome_viagem[], DATA d_inicio, DATA d_fim){
    CLIENTE *ccliente=pcc->pointerc;
    while (ccliente->id != id_cliente){      // find cliente para inserir hist
        ccliente=ccliente->pnext;
    }

    H_Clientes *hist=(H_Clientes*)malloc(sizeof(H_Clientes));
    hist->nome_viagem=(char*)malloc(sizeof(char) * (strlen(nome_viagem) + 1));
    nome_viagem=ccliente->viagens.pointerviag->nomeviagem;
    strcpy(hist->nome_viagem, nome_viagem);
    hist->data_inicio=d_inicio;
    hist->data_fim=d_fim;
    hist->pnext=NULL;

    //1st case, Empty List
    if (ccliente->hclientes->pointerhc == NULL || ccliente->hclientes->nr_historico == 0) {
        ccliente->hclientes->pointerhc=hist;
        ccliente->hclientes->nr_historico++;
        return;
    }

    //se ja houver historico
    H_Clientes *anterior=NULL;
    H_Clientes *atual=ccliente->hclientes->pointerhc;

    while (atual != NULL){ //NULL e o ultimo
        anterior=atual;
        atual=atual->pnext;
    }
    anterior->pnext=hist;
    hist->pnext=atual;
    ccliente->hclientes->nr_historico++;

}

/**
 * Função printar historico de um cliente
 * @param cc
 */
void print_historico(CLASSCLIENTE cc, int id_cliente) {
    if(cc.pointerc==0 || cc.totalclientes==0 || cc.pointerc->viagens.totalviagens==0){
        printf("Erro!!\n\n");
        return;
    }
    CLIENTE *cli = find_cliente_nif(&cc, id_cliente);
    H_Clientes *paux=cli->hclientes->pointerhc;
    while (paux != NULL) {
        printf("Historico do cliente: %d\n",id_cliente);
        printf("Nome da Viagem: %s\n",paux->nome_viagem);
        printf("Data inicio da viagem: %d/%d/%d\n",paux->data_inicio.dia,paux->data_inicio.mes,paux->data_inicio.ano);
        printf("Data fim da viagem: %d/%d/%d\n",paux->data_fim.dia,paux->data_fim.mes,paux->data_fim.ano);
        paux = paux->pnext;
    }
}
