#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Viagens        ////////////////////////////////////////////////

/**
 * Função criar dyn array de viagens quando inserimos clientes
 * @param pcl
 * @param init_size passed in insert_cliente
 */
void create_dynarray_classviagens(CLIENTE *pcl, int init_size){
    VIAGENS *pviag = (VIAGENS*)calloc(init_size, sizeof(VIAGENS));
    pcl->viagens.pointerviag=pviag;
    pcl->viagens.totalviagens=init_size;
}

/**
 * Função inserir viagem num cliente
 * @param pcl
 * @param nome_cliente
 * @param nomeviag
 * @param date
 * @param id_viagem
 * @param cidades
 */
void insert_viagens_dyn_array(CLASSCLIENTE *pcl,char nome_cliente[], char nomeviag[], DATA date, int id_viagem, int cidades) {
    int i = 0;
    CLIENTE *ccliente=pcl->pointerc;

    for (int j = 0; j < pcl->totalclientes && strcmp(nome_cliente,ccliente->nome)!=0; j++) {    //checking cliente
        ccliente=ccliente->pnext;
    }
    if(ccliente==NULL)return;

    VIAGENS *pviag =ccliente->viagens.pointerviag;

    if(ccliente->viagens.n_viagens==0){//caso seja a primeira viagem a ser inserida
        //printf("Insercao direta!\n");
        pviag->nomeviagem = (char *) malloc(strlen(nomeviag) + 1);
        strcpy(pviag->nomeviagem, nomeviag);
        //printf("Nome:%s\n",nomeviag);
        pviag->dataviagem = date;
        pviag->id = id_viagem;
        //printf("ID:%d\n\n",id_viagem);
        ccliente->viagens.n_viagens++;
        ccliente->viagens.totalviagens=5;
        create_dynarray_classcidades(pviag,cidades);    //creating dyn array cidades para cada viagem
        pviag->cidades_visitadas.totalcidades=cidades;
        return;
    }

    if (ccliente->viagens.n_viagens==ccliente->viagens.totalviagens) {  //resize pois é preciso + espaço
        int oldsize = ccliente->viagens.totalviagens;
        int newsize = oldsize + 5;
        ccliente->viagens.pointerviag = (VIAGENS *) realloc(ccliente, newsize * sizeof(VIAGENS));
        ccliente->viagens.totalviagens = newsize;
        pviag = ccliente->viagens.pointerviag + oldsize;
        for (i = oldsize; i < newsize; i++){
            pviag->nomeviagem = NULL;
            pviag->dataviagem.dia=0,pviag->dataviagem.mes=0,pviag->dataviagem.ano=0;
            pviag->id = 0;
            pviag->cidades_visitadas.totalcidades=0,pviag->cidades_visitadas.pointercid=NULL;
            pviag++;
        }
        pviag= ccliente->viagens.pointerviag+oldsize;
        pviag->nomeviagem = (char *) malloc(strlen(nomeviag) + 1);
        strcpy(pviag->nomeviagem, nomeviag);
        //printf("Nome:%s\n",nomeviag);
        pviag->dataviagem = date;
        pviag->id = id_viagem;
        //printf("ID:%d\n\n",id_viagem);
        ccliente->viagens.n_viagens++;
        create_dynarray_classcidades(pviag,cidades);    //creating dyn array cidades para cada viagem
        pviag->cidades_visitadas.totalcidades=cidades;
        return;
    }

    for (i; i <= ccliente->viagens.n_viagens; i++) {      //insercao no meio do array
        if (pviag->nomeviagem == NULL) {
            pviag->nomeviagem = (char *) malloc(strlen(nomeviag) + 1);
            strcpy(pviag->nomeviagem, nomeviag);
            //printf("Nome:%s\n",nomeviag);
            pviag->dataviagem = date;
            pviag->id = id_viagem;
            //printf("ID:%d\n\n",id_viagem);
            ccliente->viagens.n_viagens++;
            create_dynarray_classcidades(pviag,cidades);    //creating dyn array cidades para cada viagem
            pviag->cidades_visitadas.totalcidades=cidades;
            return;
        }
        pviag++;
    }
}


/**
 * Função print Viagens
 * @param pcl
 */
void print_viagens(CLASSCLIENTE pcl){
    if (pcl.pointerc->viagens.pointerviag == NULL || pcl.pointerc->viagens.totalviagens == 0){
        printf("Nao existem viagens!!\n\n");
    }
    CLIENTE *cliente=pcl.pointerc;

    while (cliente != NULL){
        VIAGENS *pviagem=cliente->viagens.pointerviag;
        if(pviagem != NULL || cliente->viagens.n_viagens != 0){ //entre aqui se o cliente tiver feito alguma viagem
            int i=0;
            while (i<cliente->viagens.n_viagens){       //n_viagens=viagens feitas pelo cliente
                printf("Cliente:%s\n", cliente->nome);
                printf("Id viagem:%d\n", pviagem->id);
                printf("Nome viagem:%s\n", pviagem->nomeviagem);
                printf("Data: %d/%d/%d\n", pviagem->dataviagem.dia, pviagem->dataviagem.mes, pviagem->dataviagem.ano);
                printf("Cidades: %d\n\n",pviagem->cidades_visitadas.totalcidades);
                pviagem++;
                i++;
            }               // depois de imprimir as viagens do cliente vamos ao próximo, cliente=cliente->pnext
        }
        cliente=cliente->pnext;
    }
}


/**
 * Função editar cidades, podemos editar o nome e a data
 * id_viagem tratado como serial nunca pode ser alterado por cliente
 * @param pcl
 */
void edit_viagens(CLASSCLIENTE pcc, char nome_cliente[], int id_viagem, char new_name[], DATA new_date){  //muda nome e data
    CLIENTE *cliente=pcc.pointerc;
    VIAGENS *viag= find_viagem_id(pcc, id_viagem);
    VIAGENS *aux=cliente->viagens.pointerviag;

    for (int i = 0; i < pcc.totalclientes; i++) {       //pointer recebido de find_viagem só indica o pointer da viagem que queremos, temos de ver se o cliente coincide com esse pointer
        if (strcmp(cliente->nome,nome_cliente) != 0 ){
            cliente=cliente->pnext;
            aux=cliente->viagens.pointerviag;
        }
        else if(cliente->viagens.n_viagens > 1){
                if(aux != viag) {
                    aux++;
                    break;
                }
        }
    }

    if(aux != NULL){        //editar viagem pretendida
        aux->nomeviagem=(char *) malloc(strlen(new_name) + 1);
        strcpy(aux->nomeviagem, new_name);
        aux->dataviagem=new_date;
    }

}

/**
 * Função find viagem por name
 * @param pcc
 * @param name
 */
VIAGENS * find_viagem_nome(CLASSCLIENTE pcc, char name[]){
    CLIENTE *cliente=pcc.pointerc;

    while (cliente != NULL) {
        VIAGENS *pv = cliente->viagens.pointerviag;
        for (int i = 0; i < cliente->viagens.n_viagens; i++) {
            if (strcmp(pv->nomeviagem, name) == 0) {
                return pv;
            }
            if(cliente->viagens.n_viagens>1)pv++;
        }
        cliente=cliente->pnext;
    }
    return NULL;
}

/**
 * Função find viagem por id
 * @param pcc
 * @param id
 */
VIAGENS * find_viagem_id(CLASSCLIENTE pcc, int id){
    CLIENTE *cliente=pcc.pointerc;
    while (cliente != NULL) {
        VIAGENS *pv = cliente->viagens.pointerviag;
        for (int i = 0; i < cliente->viagens.n_viagens; i++) {
            if(pv->id==id){
                return pv;
            }
            if(cliente->viagens.n_viagens>1)pv++;       //mesmo cliente com 2ou+ viagens precisamos de mudar o pointer antes de ver o proximo cliente
        }
        cliente=cliente->pnext;
    }
    return NULL;

}


/**
 * Função remove viagem por id
 * @param pcl
 * @param id
 */
void remove_viagem_byid(CLASSCLIENTE *pcl, char name[], int id_viagem) {
    CLIENTE *cliente=pcl->pointerc;
    for (int i = 0; i < pcl->totalclientes; i++) {
        if (strcmp(cliente->nome, name) == 0) {
            break;
        } else
            cliente=cliente->pnext;
    }

    VIAGENS *pviag = find_viagem_id(*pcl, id_viagem);
    if (pviag != NULL) {   //se existir viagem

        VIAGENS *viag_seguinte=pviag;

        //clientes com 1+ viagem,pviag_seguinte só incrementado depois de saber se o next pointer não é NULL
        //senao precisamos de trocar de cliente antes de incrementar o pointer
        if(pcl->pointerc->viagens.n_viagens > 1) {
            viag_seguinte = pviag;
        } else viag_seguinte++;

        //VIAGENS *viag_seguinte=pviag+1;
        if (viag_seguinte==NULL) { //se for ultima viagem mete tudo a null e da return
            pviag->nomeviagem=NULL;
            pviag->dataviagem.dia=0,pviag->dataviagem.mes=0,pviag->dataviagem.ano=0;
            pviag->id=0;
            pviag->cidades_visitadas.totalcidades=0;
            pviag->cidades_visitadas.pointercid=NULL;
            pviag->cidades_visitadas.n_cidades=0;
            printf("Viagem removida %d",pviag->id);
            return;
        }

        //se estiver no meio ou no inicio
        VIAGENS *viag_atual=pviag;
        for ( int i =0 ; i <pcl->pointerc->viagens.n_viagens; i++) {
            if(cliente->viagens.n_viagens > 1 && i>1){          //i=1 porque se for a primeira viagem não entra no if e insere em baixo
                pviag=pcl->pointerc->pnext->viagens.pointerviag;
                viag_atual=pviag;
                viag_seguinte=pviag;
                viag_atual->nomeviagem=viag_seguinte->nomeviagem;
                viag_atual->id=viag_seguinte->id;
                viag_atual->dataviagem.dia=viag_seguinte->dataviagem.dia;
                viag_atual->dataviagem.mes=viag_seguinte->dataviagem.mes;
                viag_atual->dataviagem.ano=viag_seguinte->dataviagem.ano;
                viag_atual->cidades_visitadas.totalcidades=viag_seguinte->cidades_visitadas.totalcidades;
                viag_atual->cidades_visitadas.pointercid=viag_seguinte->cidades_visitadas.pointercid;
                viag_atual->cidades_visitadas.n_cidades=viag_seguinte->cidades_visitadas.n_cidades;
                viag_seguinte++;
                break;
            }
            pviag++;
            viag_atual->nomeviagem=viag_seguinte->nomeviagem;
            viag_atual->id=viag_seguinte->id;
            viag_atual->dataviagem.dia=viag_seguinte->dataviagem.dia;
            viag_atual->dataviagem.mes=viag_seguinte->dataviagem.mes;
            viag_atual->dataviagem.ano=viag_seguinte->dataviagem.ano;
            viag_atual->cidades_visitadas.totalcidades=viag_seguinte->cidades_visitadas.totalcidades;
            viag_atual->cidades_visitadas.pointercid=viag_seguinte->cidades_visitadas.pointercid;
            viag_atual->cidades_visitadas.n_cidades=viag_seguinte->cidades_visitadas.n_cidades;
            viag_atual++;    //atual passa a seguinte
            viag_seguinte++;
        }
        cliente->viagens.totalviagens--;
        cliente->viagens.n_viagens--;
    }

}


/**
 * Função libertar memoria de array dyn
 * @param pcc
 */
void free_dynarray_classviagens(CLASSCLIENTE *pcc){
    VIAGENS *pv = pcc->pointerc->viagens.pointerviag;
    if(pv==NULL){
        printf("Nao existem viagens para libertar!!\n");
        return;
    }
    for (int i = 0; i < pcc->pointerc->viagens.totalviagens; ++i) {
        free(pv->nomeviagem);
    }
    free(pv);
}


/**
 * Função guardar viagens no ficheiro txt
 * @param pcl
 * @param filename
 */
void save_viagens_txt(CLASSCLIENTE pcl, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"w");
    if(fp==NULL){
        printf("ERROR!\n");
        return;
    }
    if (pcl.pointerc->viagens.pointerviag == NULL && pcl.pointerc->viagens.totalviagens==0){     //não existem viagens
        printf("Não existem viagens!!\n");
    }

    fprintf(stdout, "save_viagens_txt(%s): saving viagens...\n", filename);
    while (pcl.pointerc != NULL) {
        VIAGENS *new=pcl.pointerc->viagens.pointerviag;
        if (new != NULL ||  pcl.pointerc->viagens.n_viagens != 0) {
            int i = 0;
            while (i < pcl.pointerc->viagens.n_viagens) {
                fprintf(fp, "Cliente: %s, Id: %d, Nome: %s, Data: %d/%d/%d, Cidades: %d\n",pcl.pointerc->nome,new->id, new->nomeviagem, new->dataviagem.dia, new->dataviagem.mes, new->dataviagem.ano,pcl.pointerc->viagens.totalviagens);
                new++;
                i++;
            }
        }
        pcl.pointerc=pcl.pointerc->pnext;
    }

    fprintf(stdout, "save_viagens_txt(%s): file closed.\n", filename);
    fclose(fp);
}

/**
 * Função ler viagens do ficheiro txt
 * @param pcl
 * @param filename
 */
void read_viagens_txt(CLASSCLIENTE *pcl, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("ERROR!! %s\n",filename);
        return;
    }
    if (pcl->pointerc->viagens.pointerviag == NULL && pcl->pointerc->viagens.totalviagens==0){     //não existem viagens
        printf("Não existem viagens!\n");
    }

    int id, cidades = 0;
    char lixo[50],nome_cliente[50],nome[50];
    DATA date;

    //fprintf(stdout, "read_viagens_txt(%s): reading viagens...\n", filename);
    // %*s limpa tudo ate ao primeiro espaco
    // i)   read until ':' (everything not ':') -> %[^:]
    // ii)  ignore ':'                          -> %*[:]
    // %[^:] %*[:] read and ignore == lixo

    // Line format: "Cliente: %s, Id: %d, Nome: %s, Data: %d/%d/%d, Cidades: %d"
    for (int i = 0; i < pcl->pointerc->viagens.totalviagens-1; i++) {
        fscanf(fp,"%[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %d %*[,] %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %d %*[/] %d %*[/] %d %[^:] %*[:] %d",
               lixo,nome_cliente,lixo,&id,lixo,nome,lixo,&date.dia,&date.mes,&date.ano,lixo,&cidades);
        insert_viagens_dyn_array(pcl,nome_cliente,nome,date,id,cidades);
    }
    //fprintf(stdout, "read_viagens_txt(%s): file closed.\n", filename);
    fclose(fp);
}


/**
 * Função guardar viagens no ficheiro bin
 * @param pcl
 * @param filename
 */
void save_viagens_bin(CLASSCLIENTE cc, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"wb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }
    CLIENTE *pc=cc.pointerc;
    // Line format: "Cliente: %s, Id: %d, Nome: %s, Data: %d/%d/%d, Cidades: %d"

    while (pc != NULL) {
        VIAGENS *viag=pc->viagens.pointerviag;

            if(viag!= NULL || pc->viagens.n_viagens != 0){ //entre aqui se o cliente tiver feito alguma viagem
            int i=0;
            while (i<pc->viagens.n_viagens){       //n_viagens=viagens feitas pelo cliente
                int size_cliente = strlen(pc->nome) + 1;// tamanho de nome  +1
                fwrite(&size_cliente, sizeof(int), 1, fp);   // tamanho de nome
                fwrite(pc->nome, sizeof(char), size_cliente, fp);//escreve nome
                fwrite(&(viag->id), sizeof(int), 1, fp);//escrece ID
                int size_nome = strlen(viag->nomeviagem) + 1;// tamanho de nomeviagem  +1
                fwrite(&size_nome, sizeof(int), 1, fp);   // tamanho de nomeviagem
                fwrite(viag->nomeviagem, sizeof(char), size_nome, fp);//escreve nomeviagem
                fwrite(&(viag->dataviagem.dia), sizeof(float), 1, fp); //dia
                fwrite(&(viag->dataviagem.mes), sizeof(float), 1, fp); //mes
                fwrite(&(viag->dataviagem.ano), sizeof(float), 1, fp); //ano
                fwrite(&(viag->cidades_visitadas.totalcidades), sizeof(int), 1, fp);//escreve size
                viag++;
                i++;
            }
        }
        pc=pc->pnext;
    }

    fclose(fp);
}


/**
 * Função ler viagens do ficheiro bin
 * @param pcl
 * @param filename
 */
void read_viagens_bin(CLASSCLIENTE *pcs, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"rb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }

    int id=0,size_nome=0,size_viagem=0,cidades=0;
    char nome_cliente[50]="",nome_viagem[50]="";
    DATA date;

    CLIENTE *pc=pcs->pointerc;
    while (pc != NULL) {
        VIAGENS *viag=pc->viagens.pointerviag;

        if(viag!= NULL || pc->viagens.n_viagens != 0){ //entre aqui se o cliente tiver feito alguma viagem
            int i=0;
            while (i<pc->viagens.n_viagens){       //n_viagens=viagens feitas pelo cliente
                fread(&size_nome, sizeof(int), 1, fp);//ler tamanho nomeviagem
                fread(nome_viagem, sizeof(char), size_nome, fp);//ler nomeviagem
                fread(&id, sizeof(int), 1, fp);//le id
                fread(&size_viagem, sizeof(int), 1, fp);//ler tamanho nomeviagem
                fread(nome_viagem, sizeof(char), size_viagem, fp);//ler nomeviagem
                fread(&date.dia, sizeof(float), 1, fp);//
                fread(&date.mes, sizeof(float), 1, fp);//
                fread(&date.ano, sizeof(float), 1, fp);//
                fread(&cidades, sizeof(int), 1, fp);//le cidades
                insert_viagens_dyn_array(pcs, nome_cliente, nome_viagem, date, id, cidades);
                viag++;
                i++;
            }
        }
        pc=pc->pnext;
    }

    fclose(fp);
}


/**
 * Função auxiliar para comparar datas
 * @param dt1
 * @param dt2
 */
int date_cmp(DATA dt1, DATA dt2){
    if (dt1.ano > dt2.ano || dt1.ano < dt2.ano)    //diferente
        return 1;

    if (dt1.ano == dt2.ano){
        if (dt1.mes<dt2.mes)
            return -1;
        else if (dt1.mes>dt2.mes)
            return 1;
        else if (dt1.dia<dt2.dia)
            return -1;
        else if(dt1.dia>dt2.dia)
            return 1;
        else
            return 0;               //same date
    }
}


/**
 * Função para imprimir em relatorio todas as viagens (+ cidades visitadas) de um cliente numa determinada data
 * @param pcl
 * @param nome_cliente
 * @param date
 */
void print_relatorio_viagens_cidades_dateX(CLASSCLIENTE *pcl, char nome_cliente[], DATA date) {
    CLIENTE *cliente = pcl->pointerc;
    if (cliente == NULL)return;
    puts("\t----RELATORIO VIAGENS V1----\n");
    for (int i = 0; i < pcl->totalclientes; i++) {
        if (strcmp(cliente->nome, nome_cliente) == 0) { //finding cliente
            break;
        } else
            cliente = cliente->pnext;
    }

    printf("Cliente:%s\n", cliente->nome);
    VIAGENS *pviagem = cliente->viagens.pointerviag;
    CIDADES *cid=pviagem->cidades_visitadas.pointercid;

    for (int i = 0; i < cliente->viagens.totalviagens; ++i) { //(pviagem != NULL || cliente->viagens.n_viagens != 0) { //entre aqui se o cliente tiver feito alguma viagem
        int j = 0;
        while (j < cliente->viagens.n_viagens) {       //n_viagens=viagens feitas pelo cliente

            if(date_cmp(pviagem->dataviagem,date)==0){  //existe viagem naquela data
                printf("Viagens realizadas em %d/%d/%d\n", pviagem->dataviagem.dia, pviagem->dataviagem.mes, pviagem->dataviagem.ano);
                printf("Id viagem:%d\n", pviagem->id);
                printf("Viagem:%s\n", pviagem->nomeviagem);
                printf("Numero cidades visitadas:%d\n", pviagem->cidades_visitadas.n_cidades);
                for (int k = 0; k < pviagem->cidades_visitadas.n_cidades; k++) {    //print todas cidades visitadas na viagem
                    printf("\tNome cidade:%s\n", cid->nomecidade);
                    cid++;
                }
                j++;
            }
            j++;    //data viagem nao coincide mas incrementamos j para nao ultrapassar n_viagens
            pviagem++;                                   //clientes com 2ou+ viagens mudamos o pointer para a proxima viagem
            cid=pviagem->cidades_visitadas.pointercid;   //atualizamos cid para as cidades visitadas na viagem seguinte, senao imprimia as cidades da 1ª viagem realizada
        }
    }

}


/**
 * Função para imprimir,em relatorio, uma pesquisa de viagem dando uma cidade
 * @param pcl
 * @param nome_cliente
 * @param nome_cidade
 */
void print_relatorio_viagem_cidadeX(CLASSCLIENTE *pcl, char nome_cliente[], char nome_cidade[]) {
    CLIENTE *cliente = pcl->pointerc;
    if (cliente == NULL)return;
    puts("\t----RELATORIO VIAGENS V2----\n");
    for (int i = 0; i < pcl->totalclientes; i++) {
        if (strcmp(cliente->nome, nome_cliente) == 0) { //finding cliente
            break;
        } else
            cliente = cliente->pnext;
    }

    printf("Cliente:%s\n", cliente->nome);
    VIAGENS *pviagem = cliente->viagens.pointerviag;
    CIDADES *cid=pviagem->cidades_visitadas.pointercid;

    for (int i = 0; i < cliente->viagens.totalviagens; ++i) { //(pviagem != NULL || cliente->viagens.n_viagens != 0) { //entre aqui se o cliente tiver feito alguma viagem
        int j = 0;
        while (j < cliente->viagens.n_viagens) {       //n_viagens=viagens feitas pelo cliente

            while (j<pviagem->cidades_visitadas.n_cidades){         //cliente com 2+ viagens depois de terminar todas cidades da sua 1ª viagem, incrementamos pointer

                if(strcmp(cid->nomecidade,nome_cidade)==0){         //imprime a pesquisa desejada
                    printf("Id viagem:%d\n", pviagem->id);
                    printf("Viagem:%s\n", pviagem->nomeviagem);
                    printf("Numero cidades visitadas:%d\n", pviagem->cidades_visitadas.n_cidades);
                    printf("Nome cidade procurada:%s\n", cid->nomecidade);
                    return;
                }
                cid++;
                j++;
            }
            pviagem++;                                   //clientes com 2ou+ viagens mudamos o pointer para a proxima viagem
            cid=pviagem->cidades_visitadas.pointercid;   //atualizamos cid para as cidades visitadas na viagem seguinte, senao imprimia as cidades da 1ª viagem realizada
        }
    }

}


/**
 * Função para imprimir,em relatorio, uma pesquisa de cidade dando um Ponto Interesse Pol
 * @param pcl
 * @param nome_cliente
 * @param nome_cidade
 */
void print_relatorio_viagem_PolX(CLASSCLIENTE *pcl, char nome_cliente[], char local_visitado[]) {
    CLIENTE *cliente = pcl->pointerc;
    if (cliente == NULL)return;
    puts("\t----RELATORIO VIAGENS V3----\n");
    for (int i = 0; i < pcl->totalclientes; i++) {
        if (strcmp(cliente->nome, nome_cliente) == 0) { //finding cliente
            break;
        } else
            cliente = cliente->pnext;
    }

    printf("Cliente:%s\n", cliente->nome);
    VIAGENS *pviagem = cliente->viagens.pointerviag;
    CIDADES *cid=pviagem->cidades_visitadas.pointercid;

    for (int i = 0; i < cliente->viagens.totalviagens; ++i) { //(pviagem != NULL || cliente->viagens.n_viagens != 0) { //entre aqui se o cliente tiver feito alguma viagem
        int j = 0;
        while (j < cliente->viagens.n_viagens) {       //n_viagens=viagens feitas pelo cliente

            while (j<pviagem->cidades_visitadas.n_cidades){         //cliente com 2+ viagens depois de terminar todas cidades da sua 1ª viagem, incrementamos pointer

                if(strcmp(cid->pontosInt.ppol->nome_local, local_visitado) == 0){         //imprime a pesquisa desejada
                    printf("Id viagem:%d\n", pviagem->id);
                    printf("Viagem:%s\n", pviagem->nomeviagem);
                    printf("Numero cidades visitadas:%d\n", pviagem->cidades_visitadas.n_cidades);
                    printf("Id cidade:%d\n", cid->ID);
                    printf("Nome cidade:%s\n", cid->nomecidade);
                    printf("Pontos Visitados:%s\n", cid->pontosInt.ppol->nome_local);

                    return;
                }
                cid++;
                j++;
            }
            pviagem++;                                   //clientes com 2ou+ viagens mudamos o pointer para a proxima viagem
            cid=pviagem->cidades_visitadas.pointercid;   //atualizamos cid para as cidades visitadas na viagem seguinte, senao imprimia as cidades da 1ª viagem realizada
        }
    }

}