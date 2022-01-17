#include "functions.h"
#include <stdio.h>
#include "string.h"

/////////////////////////////////////////////////       Cidades        ////////////////////////////////////////////////

/**
 * Função criar dyn array de cidades
 * @param pcl
 * @param init_size passed in insert_cliente
 */
void create_dynarray_classcidades(VIAGENS *pv, int initsize){
    CIDADES *pcid=(CIDADES *)calloc(initsize, sizeof(CIDADES));
    pv->cidades_visitadas.pointercid=pcid;
    pv->cidades_visitadas.totalcidades=initsize;
}

/**
 * Função inserir cidade nua viagem
 * @param pcl
 * @param viagem
 * @param name
 * @param id
 * @param desc
 * @param latitude
 * @param longitude
 */
void insert_cidade_dynarray(CLASSCLIENTE *pcl, char viagem[], char name[], int id, char desc[], float latitude, float longitude) {
    int i = 0;

    CLIENTE *pc=pcl->pointerc;
    VIAGENS *pviag=pc->viagens.pointerviag;
    CIDADES *pcid=pviag->cidades_visitadas.pointercid;

    for (int j = 0; j < pc->viagens.totalviagens; j++) {    //checking nome viagem
        if (strcmp(viagem, pviag->nomeviagem)==0) break;
        else {
            if(pviag->cidades_visitadas.n_cidades==pviag->cidades_visitadas.totalcidades) {  //Viagem cliente X tem todas viagens realizadas
                        //entra para mudar pcliente para pnext porque todas cidades foram inseridas
                int k=1;
                while (k<pc->viagens.n_viagens && pviag->cidades_visitadas.n_cidades==pviag->cidades_visitadas.totalcidades){   //Se cliente tiver 2ou+ viagens
                    if (pc->viagens.n_viagens > 1) {
                        pviag = pviag + 1;
                        pcid=pviag->cidades_visitadas.pointercid;
                    }
                    k++;
                }
                if(strcmp(viagem, pviag->nomeviagem)!=0){      //depois de verificar se cliente tem 2ou+ viagens e de inserir todas as cidades das mesmas, voltamos aqui para o proximo cliente
                if(k!=2)pc = pc->pnext;
                pviag = pc->viagens.pointerviag;
                pcid = pviag->cidades_visitadas.pointercid;
                }
            }
        }
    }

    if(pviag->cidades_visitadas.n_cidades==0){ //caso seja a primeira cidade a ser inserida
        //printf("Insercao direta!\n");
        pcid->nomecidade = (char *) malloc(strlen(name) + 1);
        strcpy(pcid->nomecidade, name);
        pcid->ID=id;
        pcid->descricao=(char*)malloc(strlen(desc) + 1);
        strcpy(pcid->descricao,desc);
        pcid->coordenadas.x=latitude;
        pcid->coordenadas.y=longitude;
        pviag->cidades_visitadas.n_cidades++;   //cidades_visitas++
        create_pol(pcid,3);
        pcid->pontosInt.totalpontos=3;
        return;
    }

    // n_cidades visitas == size array cidades ->resize
    if (pviag->cidades_visitadas.n_cidades == pviag->cidades_visitadas.totalcidades) {  //resize pois é preciso + espaço
        int oldsize = pviag->cidades_visitadas.totalcidades;
        int newsize = oldsize + 5;
        pcid=(CIDADES *)realloc(pcid, newsize * sizeof(CIDADES));
        pviag->cidades_visitadas.totalcidades=newsize;
        pcid = pcid + oldsize;
        for (i = oldsize; i < newsize; i++){
            pcid->ID=0;
            pcid->nomecidade = NULL;
            pcid->descricao=NULL;
            pcid->coordenadas.x=0.0f,pcid->coordenadas.y=0.0f;
            pcid++;
        }
        pcid= pcid + oldsize;
        pcid->nomecidade = (char *) malloc(strlen(name) + 1);
        strcpy(pcid->nomecidade, name);
        pcid->ID=id;
        pcid->descricao=(char*)malloc(strlen(desc) + 1);
        strcpy(pcid->descricao,desc);
        pcid->coordenadas.x=latitude;
        pcid->coordenadas.y=longitude;
        pviag->cidades_visitadas.n_cidades++;   //cidades_visitas++
        create_pol(pcid,3);
        pcid->pontosInt.totalpontos=3;
        return;
    }

    for (i=0; i < pviag->cidades_visitadas.totalcidades; i++) {        //inserir cidades na mesma viagem (n_cidades !=0)
        if (pcid->nomecidade == NULL) {
            pcid->nomecidade = (char *) malloc(strlen(name) + 1);
            strcpy(pcid->nomecidade, name);
            pcid->ID=id;
            pcid->descricao=(char*)malloc(strlen(desc) + 1);
            strcpy(pcid->descricao,desc);
            pcid->coordenadas.x=latitude;
            pcid->coordenadas.y=longitude;
            pviag->cidades_visitadas.n_cidades++;   //cidades_visitas++
            create_pol(pcid,3);
            pcid->pontosInt.totalpontos=3;
            return;
        }
        pcid++;
    }

}

/**
 * Função que imprime todos os clientes,todas as suas viagens e os que nao tem cidades fica a NULL/0
 * Isto porque temos o read_clientes e o read_viagens
 * @param cc
 */
void print_cidades(CLASSCLIENTE cc) {
    if (cc.pointerc->viagens.pointerviag->cidades_visitadas.pointercid == NULL && cc.pointerc->viagens.pointerviag->cidades_visitadas.totalcidades == 0){
        printf("Nao existem cidades!!\n");
    }

    while (cc.pointerc != NULL) {
        VIAGENS *pviag=cc.pointerc->viagens.pointerviag;

        while (pviag->nomeviagem != NULL) {
            printf("\t\t%s\n",cc.pointerc->nome);
            CIDADES *pcid = pviag->cidades_visitadas.pointercid;
            if (pcid != NULL || pviag->cidades_visitadas.n_cidades != 0) {      //existe cid neste pointerviag
                int i = 0;
                while (i < pviag->cidades_visitadas.totalcidades) {       //n_cidades=cidades visitas na viagem do cliente
                    printf("Viagem:%s\n", pviag->nomeviagem);
                    printf("ID:%d\n", pcid->ID);
                    printf("Nome:%s\n", pcid->nomecidade);
                    printf("Descricao:%s\n", pcid->descricao);
                    printf("Latitude:%0.2f\n", pcid->coordenadas.x);
                    printf("Longitude:%0.2f\n", pcid->coordenadas.y);
                    printf("Pontos:%s\n\n",pcid->pontosInt.ppol->nome_local);
                    pcid++;
                    i++;
                }
                printf("----------------------------------\n");
            }
            //mudar pviag porque todas cidades visitadas daquela viagem já foram feitas
            pviag++;
        }
        cc.pointerc=cc.pointerc->pnext;
    }

}


/**
 * Função editar nome,descricao e coordenadas de uma cidade
 * @param pcc
 * @param id_cidade
 * @param nome
 * @param novadesc
 * @param x
 * @param y
 *
 */
void edit_cidades(CLASSCLIENTE pcc, char nome_viagem[],int id_cidade, char new_name[], char new_desc[], float latit, float longi){
    CLIENTE *cliente=pcc.pointerc;
    VIAGENS *viag= find_viagem_nome(pcc,nome_viagem);
    CIDADES *cid= find_cidade_ID(&pcc,id_cidade);            //cidade que queremos modificar
    CIDADES *aux_cid=viag->cidades_visitadas.pointercid;    //cópia da cidade que vamos modificar

    for (int i = 0; i < cliente->viagens.totalviagens; i++) {       //pointer recebido de find_viagem só indica o pointer da viagem que queremos, temos de ver se o cliente coincide com esse pointer
        if (strcmp(viag->nomeviagem,nome_viagem) != 0 ){
            cliente=cliente->pnext;
            viag=cliente->viagens.pointerviag;
        }
        if(aux_cid == cid){
            break;
        }
        else if(cid != viag->cidades_visitadas.pointercid) {
                aux_cid++;
        }

    }

    if(aux_cid != NULL){        //editar cidade pretendida
        aux_cid->nomecidade=(char *) malloc(strlen(new_name) + 1);
        strcpy(cid->nomecidade, new_name);
        aux_cid->descricao=(char *) malloc(strlen(new_desc) + 1);
        strcpy(cid->descricao, new_desc);
        aux_cid->coordenadas.x=latit;
        aux_cid->coordenadas.y=longi;
    }

}


/**
 * Função procurar cidade por nome
 * @param cc
 * @param nome
 */
CIDADES * find_cidade_nome(CLASSCLIENTE cc, char nome[]){
    CLIENTE *clt=cc.pointerc;

    while (clt != NULL){
        int i=0;
        while (i<clt->viagens.n_viagens) {// entra se cliente tiver viagem realizadas
            VIAGENS *viag=clt->viagens.pointerviag;
            if(i==1) viag++;    //i==1 estamos na 2ª iteracao do ciclo, cliente em 2 viagens e mudamos pointer para 2ª viagem do cliente
            CIDADES *cid=viag->cidades_visitadas.pointercid;

            for (int j = 0; j < clt->viagens.pointerviag->cidades_visitadas.n_cidades; j++) {   //n_cidades visitadas
                if (strcmp(cid->nomecidade, nome) == 0) {
                    return cid;
                }
                //ultima cidade da viagem, pointer nao pode ser incrementado senao aponta para NULL
                //j==4 é ultima iteracão deste ciclo for, não queremos incrementar o cid porque vamos perder o pointer da cidade
                if (j==viag->cidades_visitadas.totalcidades-1) break;
                cid++;
            }
            i++;
        }

        clt=clt->pnext;                     //atualizar cliente e o seu pointer para cidades também precisa de ser atualizado
    }
    return NULL;
}


/**
 * Função procurar cidade por id
 * @param cc
 * @param nome
 */
CIDADES * find_cidade_ID(CLASSCLIENTE *pcc, int id){
    CLIENTE *clt=pcc->pointerc;

    while (clt != NULL){
        int i=0;
        while (i<clt->viagens.n_viagens) {// entra se cliente tiver viagem realizadas
            VIAGENS *viag=clt->viagens.pointerviag;
            if(i==1) viag++;    //i==1 estamos na 2ª iteracao do ciclo, cliente em 2 viagens e mudamos pointer para 2ª viagem do cliente
            CIDADES *cid=viag->cidades_visitadas.pointercid;

            for (int j = 0; j < clt->viagens.pointerviag->cidades_visitadas.n_cidades; j++) {   //n_cidades visitadas
                if (cid->ID==id){
                    return cid;
                }
                //ultima cidade da viagem, pointer nao pode ser incrementado senao aponta para NULL
                //j==4 é ultima iteracão deste ciclo for, não queremos incrementar o cid porque vamos perder o pointer da cidade
                if (j==4) {
                    break;
                }else cid++;

            }
            i++;
        }

        clt=clt->pnext;                     //atualizar cliente e o seu pointer para cidades também precisa de ser atualizado
    }
    return NULL;
}


/**
 * Função remover cidade por id
 * @param cc
 * @param nome
 */
void remove_cidade_id(CLASSCLIENTE *pcc,char nome_viagem[], int id_cidade) {
    CLIENTE *cliente=pcc->pointerc;
    VIAGENS *pviag = find_viagem_nome(*pcc, nome_viagem); //pointercliente não altera

    if (pviag != NULL) {   //verificar todas cidades da viagem X
        CIDADES *pcid = find_cidade_ID(pcc, id_cidade);

        CIDADES *cid_seguinte;
        int last_cidade=cliente->viagens.pointerviag->cidades_visitadas.totalcidades;

        if(id_cidade==last_cidade && cliente->viagens.n_viagens<2) {     //cliente so tem uma viagem
            cid_seguinte = cliente->pnext->viagens.pointerviag->cidades_visitadas.pointercid;
             //se for ultima cidade mete tudo a null e da return
                pcid->nomecidade = NULL;
                pcid->coordenadas.x = 0.0f, pcid->coordenadas.y = 0.0f;
                pcid->descricao = NULL;
                pcid->ID = 0;
                pcid->pontosInt.totalpontos=0,pcid->pontosInt.ppol=NULL;
            return;
        }
        else if(id_cidade==last_cidade && cliente->viagens.n_viagens>1){ //cliente com 2+ viagens
            cid_seguinte=pcid+1;
            pcid->nomecidade = NULL;
            pcid->coordenadas.x = 0.0f, pcid->coordenadas.y = 0.0f;
            pcid->descricao = NULL;
            pcid->ID = 0;
            pcid->pontosInt.totalpontos=0,pcid->pontosInt.ppol=NULL;
            return;
        }


        //se estiver no meio ou no inicio
        cid_seguinte=pcid+1;
        CIDADES *cid_atual= pcid;
        for (int i =0 ; i <pviag->cidades_visitadas.totalcidades; i++) { //comeca no meio e vai ate ao fim
            pcid++; //substitui a cidade que foi apagada
            cid_atual->nomecidade=cid_seguinte->nomecidade;
            cid_atual->descricao=cid_seguinte->descricao;
            cid_atual->coordenadas.x=cid_seguinte->coordenadas.x;
            cid_atual->coordenadas.y=cid_seguinte->coordenadas.y;
            cid_atual->ID=cid_seguinte->ID;
            cid_atual->pontosInt=cid_seguinte->pontosInt;
            cid_atual++;    //atual passa a seguinte
            cid_seguinte++; //a cid_seguinte passa ainda mais uma para a frente até acabar o ciclo for
        }
        pviag->cidades_visitadas.n_cidades--;           //decrementar porque eliminamos um cidade visitada da viagem X
        pviag->cidades_visitadas.totalcidades--;
    }

}

/**
 * Função libertar memoria de array dyn
 * @param pcc
 */
void free_dynarray_classcidades(CLASSCLIENTE *pcc){
    CIDADES *pcid = pcc->pointerc->viagens.pointerviag->cidades_visitadas.pointercid;
    if(pcid==NULL){
        printf("Nao existem cidades para libertar\n");
        return;
    }
    for (int i = 0; i < pcc->pointerc->viagens.pointerviag->cidades_visitadas.totalcidades; ++i) {
        free(pcid->nomecidade);
    }
    free(pcid);
}


/**
 * Função guardar cidades do ficheiro txt
 * @param pcl
 * @param filename
 */
void save_cidades_txt(CLASSCLIENTE cc, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"w");
    if(fp==NULL){
        printf("ERROR!\n");
        return;
    }
    if (cc.pointerc->viagens.pointerviag->cidades_visitadas.pointercid == NULL && cc.pointerc->viagens.pointerviag->cidades_visitadas.n_cidades==0){     //não existem cidades visitadas
        printf("Não existem cidades!!\n");
    }

    fprintf(stdout, "save_cidades_txt(%s): saving cidades...\n", filename);
    while (cc.pointerc != NULL) {
        VIAGENS *pviag=cc.pointerc->viagens.pointerviag;

        while (pviag->nomeviagem != NULL) {
            CIDADES *new = pviag->cidades_visitadas.pointercid;
            if (new != NULL || pviag->cidades_visitadas.totalcidades != 0) {
                int i = 0;
                while (i < pviag->cidades_visitadas.n_cidades) {
                    fprintf(fp, "Viagem: %s, Id: %d, Nome: %s, Descricao: %s, Latitude:%f, Longitude:%f, Pontos:%s\n",pviag->nomeviagem,new->ID,new->nomecidade,new->descricao,new->coordenadas.x,new->coordenadas.y,new->pontosInt.ppol->nome_local);
                    new++;
                    i++;
                }
            }
            pviag++;
        }
        cc.pointerc=cc.pointerc->pnext;
    }

    fprintf(stdout, "save_cidades_txt(%s): file closed.\n", filename);
    fclose(fp);
}

/**
 * Função ler cidades do ficheiro txt
 * @param pcl
 * @param filename
 */
void read_cidades_txt(CLASSCLIENTE *pcc, char filename[]){
    FILE *fp=NULL;
    fp=fopen(filename,"r");
    if(fp==NULL){
        printf("ERROR!! %s\n",filename);
        return;
    }
    if (pcc->pointerc->viagens.pointerviag->cidades_visitadas.pointercid == NULL && pcc->pointerc->viagens.pointerviag->cidades_visitadas.n_cidades==0){     //não existem cidades visitadas
        printf("Não existem cidades!!\n");
    }

    CLIENTE *pc=pcc->pointerc;
    int id_cidade=0,id_cidade_pontos=1;
    float latitude,longitude;
    char lixo[100],nome_viagem[20],nome[20],descricao[100],pontos[50];

    // Viagem: %s, ID: 1, Nome: Cidade1, Descricao: %s, Latitude: 2.0, Longitude: 2.0, Pontos:%s
    // %*s limpa tudo ate ao primeiro espaco
    // i)   read until ':' (everything not ':') -> %[^:]
    // ii)  ignore ':'                          -> %*[:]
    // %[^:] %*[:] read and ignore == lixo
    while (pc != NULL) {
        VIAGENS *pviag=pc->viagens.pointerviag;

        while (pviag->nomeviagem != NULL) {
            CIDADES *new = pviag->cidades_visitadas.pointercid;
            if (new != NULL || pc->viagens.n_viagens != 0) {
                int i = 0;
                while (i < pviag->cidades_visitadas.totalcidades) {
                    fscanf(fp, "%[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %d %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %[^,] %*[,] %[^:] %*[:] %f %[^:] %*[:] %f %*[,] %[^:] %*[:] %s",lixo,nome_viagem,lixo, &id_cidade, lixo, nome, lixo, descricao, lixo, &latitude, lixo, &longitude,lixo,pontos);
                    insert_cidade_dynarray(pcc,nome_viagem, nome, id_cidade, descricao, latitude, longitude);
                    insert_pol_cidade(pcc,id_cidade_pontos,pontos);
                    id_cidade_pontos++;   //1-20
                    new++;
                    i++;
                }
            }
            pviag++;
        }
        pc=pc->pnext;
    }

    fclose(fp);
}

/**
 * Função guardar cidades do ficheiro bin
 * @param pcl
 * @param filename
 */
void save_cidades_bin(CLASSCLIENTE cc, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"wb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }
    if (cc.pointerc->viagens.pointerviag->cidades_visitadas.pointercid == NULL && cc.pointerc->viagens.pointerviag->cidades_visitadas.n_cidades==0){     //não existem cidades visitadas
        printf("Não existem cidades!!\n");
    }

    // Viagem: %s, ID: 1, Nome: Cidade1, Descricao: %s, Latitude: 2.0, Longitude: 2.0, Pontos:%s
    CLIENTE *pc=cc.pointerc;
    while (pc != NULL) {
        VIAGENS *viag=pc->viagens.pointerviag;
        while (viag->nomeviagem != NULL){ //entre aqui se o cliente tiver feito alguma viagem

            CIDADES *cid=viag->cidades_visitadas.pointercid;
            if (cid != NULL || viag->cidades_visitadas.totalcidades != 0) {
                int i = 0;
                while (i < viag->cidades_visitadas.n_cidades) {
                    int size_viagem = strlen(viag->nomeviagem) + 1;// tamanho de nomeviagem  +1
                    fwrite(&size_viagem, sizeof(int), 1, fp);   // tamanho de nomeviagem
                    fwrite(viag->nomeviagem, sizeof(char), size_viagem, fp);//escreve nomeviagem
                    fwrite(&(cid->ID), sizeof(int), 1, fp);//escrece ID

                    int size_nome = strlen(cid->nomecidade) + 1;// tamanho de nomecidade  +1
                    fwrite(&size_nome, sizeof(int), 1, fp);   // tamanho de nomecidade
                    fwrite(cid->nomecidade, sizeof(char), size_nome, fp);//escreve nomecidade

                    int size = strlen(cid->descricao) + 1;// tamanho de descricao  +1
                    fwrite(&size, sizeof(char), 1, fp);//ler tamanho descricao
                    fwrite(cid->descricao, sizeof(char), size, fp);//escreve descricao

                    fwrite(&(cid->coordenadas.x), sizeof(float), 1, fp); //latitude
                    fwrite(&(cid->coordenadas.y), sizeof(float), 1, fp); //longitude

                    int size_pontos = strlen(cid->pontosInt.ppol->nome_local) + 1;// tamanho de descricao  +1 - '\0'
                    fwrite(&size_pontos, sizeof(char*), 1, fp);//ler tamanho descricao
                    fwrite(cid->pontosInt.ppol->nome_local, sizeof(char*), size, fp);//escreve nome_local
                    cid++;
                    i++;
                }
            }
            viag++;
        }
        pc=pc->pnext;
    }

    fclose(fp);
}

/**
 * Função ler cidades do ficheiro bin
 * @param pcl
 * @param filename
 */
void read_cidades_bin(CLASSCLIENTE *pcc, char filename[]){
    FILE *fp=NULL;
    if((fp=fopen(filename,"rb"))==NULL){
        printf("Erro ao guardar o Ficheiro\n");
        return;
    }
    if (pcc->pointerc->viagens.pointerviag->cidades_visitadas.pointercid == NULL && pcc->pointerc->viagens.pointerviag->cidades_visitadas.n_cidades==0){     //não existem cidades visitadas
        printf("Não existem cidades!!\n");
    }

    CLIENTE *pc=pcc->pointerc;
    int id_cidade=0,size_viagem=0,size_nome=0,size_desc=0,size_pontos=0;
    float latitude=0.0f,longitude=0.0f;
    char nome_cidade[10],nome_viagem[10],pontos[50],descricao[50];

    // Viagem: %s, ID: 1, Nome: Cidade1, Descricao: %s, Latitude: 2.0, Longitude: 2.0, Pontos:%s
    while (pc != NULL) {
        VIAGENS *pviag=pc->viagens.pointerviag;
        while (pviag->nomeviagem != NULL) {
            CIDADES *cid = pviag->cidades_visitadas.pointercid;
            if (cid != NULL || pc->viagens.n_viagens != 0) {
                int i = 0;
                while (i < pviag->cidades_visitadas.totalcidades) {
                    fread(&size_viagem,sizeof(int),1,fp);//ler tamanho nomeviagem
                    fread(nome_viagem,sizeof(char),size_viagem,fp);//ler nomeviagem
                    fread(&id_cidade,sizeof(int),1,fp);//le id cidade

                    fread(&size_nome,sizeof(int),1,fp);//ler tamanho nomecidade
                    fread(nome_cidade,sizeof(char),size_nome,fp);//ler nomeviagem

                    fread(&size_desc, sizeof(char), 1, fp);//ler tamanho descricao
                    fread(descricao, sizeof(char), size_desc, fp);//le descricao cidade

                    fread(&latitude,sizeof(float),1,fp);//le latitude cidade
                    fread(&longitude,sizeof(float),1,fp);//le longitude cidade

                    fread(&size_pontos, sizeof(char), 1, fp);//ler tamanho descricao
                    fread(pontos, sizeof(char), size_desc, fp);//le descricao cidade
                    insert_cidade_dynarray(pcc,nome_viagem,nome_cidade,id_cidade,descricao,latitude,longitude);
                    insert_pol_cidade(pcc,id_cidade,pontos);    //error segmentation fault
                    cid++;
                    i++;
                }
            }
            pviag++;
        }
        pc=pc->pnext;
    }

    fclose(fp);
}


/**
 * Função para criar um dyn array Pol
 * @param pc
 * @param size
 */
void create_pol(CIDADES *pc, int size){
    Pol *pol=(Pol *)calloc(size, sizeof(Pol));
    pc->pontosInt.ppol=pol;
    pc->pontosInt.totalpontos=size;
}


/**
 * Função para inserir um PontoInt Pol numa cidade
 * @param pcc
 * @param id_cidade
 * @param id_cidade
 */
void insert_pol_cidade(CLASSCLIENTE *pcc, int id_cidade, char pontos[]){
    int i=0;

    CIDADES *pcid= find_cidade_ID(pcc,id_cidade);

    if(pcid->pontosInt.n_pontos==0){ //caso seja o primeiro ponto de interesse
        pcid->pontosInt.ppol->id_cid=id_cidade;
        pcid->pontosInt.ppol->nome_local=(char*) malloc(strlen(pontos) + 1);
        strcpy(pcid->pontosInt.ppol->nome_local, pontos);
        pcid->pontosInt.n_pontos++; //1 Ponto interesse
        return;
    }

    // n_cidades visitas == size array cidades ->resize
    if (pcid->pontosInt.n_pontos== pcid->pontosInt.totalpontos) {  //resize pois é preciso + espaço
        int oldsize = pcid->pontosInt.totalpontos;
        int newsize = oldsize + 5;
        Pol *pol=(Pol *)realloc(pol,newsize *sizeof(Pol));
        pcid->pontosInt.totalpontos=newsize;
        pol = pol + oldsize;
        for (i = oldsize; i < newsize; i++){
            pol->id_cid=0;
            pol->nome_local=NULL;
            pol++;
        }
        pol = pol + oldsize;
        pol->id_cid=id_cidade;
        pol->nome_local=(char*) malloc(strlen(pontos) + 1);
        strcpy(pcid->pontosInt.ppol->nome_local, pontos);
        pcid->pontosInt.n_pontos++;
        return;
    }

    for (i=0; i < pcid->pontosInt.totalpontos; i++) {        //inserir nome_local de interesse em cidades com 2ou+ pontosInt
        if (pcid->pontosInt.ppol->id_cid == 1) {
            pcid->pontosInt.ppol->id_cid=id_cidade;
            pcid->pontosInt.ppol->nome_local=(char*) malloc(strlen(pontos) + 1);
            strcpy(pcid->pontosInt.ppol->nome_local, pontos);
            pcid->pontosInt.n_pontos++;
            return;
        }
        pcid++;
    }
}


/**
 * Função para pesquisar um Ponto Interesse Pol dando um cidade
 * @param pcl
 * @param id_cidade
 */
Pol * find_pol_cidade(CLASSCLIENTE *pcl, int id_cidade){
    CLIENTE *clt=pcl->pointerc;

    while (clt != NULL){
        int i=0;
        while (i<clt->viagens.n_viagens) {// entra se cliente tiver viagem realizadas
            VIAGENS *viag=clt->viagens.pointerviag;
            if(i==1) viag++;    //i==1 estamos na 2ª iteracao do ciclo, cliente em 2 viagens e mudamos pointer para 2ª viagem do cliente
            CIDADES *cid=viag->cidades_visitadas.pointercid;

            for (int j = 0; j < clt->viagens.pointerviag->cidades_visitadas.n_cidades; j++) {   //n_cidades visitadas
                if (cid->ID==id_cidade){
                    return cid->pontosInt.ppol;
                    //printf("%s",cid->pontosInt.ppol->nome_local);
                }
                //ultima cidade da viagem, pointer nao pode ser incrementado senao aponta para NULL
                //j==4 é ultima iteracão deste ciclo for, não queremos incrementar o cid porque vamos perder o pointer da cidade
                if (j==4) {
                    break;
                }else cid++;

            }
            i++;
        }

        clt=clt->pnext;                     //atualizar cliente e o seu pointer para cidades também precisa de ser atualizado
    }
    return NULL;

}


void remove_pol(CLASSCLIENTE *pcl, int id_pol){}