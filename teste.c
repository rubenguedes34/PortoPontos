#include "functions.h"
#include <stdio.h>

CLASSCLIENTE clt = { NULL, 0};
CLASSVIAGENS_DYNARRAY viag={.pointerviag=NULL,.current_viagem=0,.totalviagens=0,.viagens_porRealizar=0,.viagens_realizadas=0};
CLASSCIDADES cid = {NULL,0};

void teste_clientes(){

    //inserir cliente
    //insert_cliente_ordered(&clt,"Ruben",1,232928185,"ruben@ufp.edu.pt");
    //insert_cliente_ordered(&clt,"Cliente1",2,123456789,"client1@ufp.edu.pt");
    //insert_cliente_ordered(&clt,"Cliente2",3,112345678,"client2@ufp.edu.pt");
    //insert_cliente_ordered(&clt,"Cliente3",4,111234567,"client3@ufp.edu.pt");
    //print_cliente(clt);

    //remoção cliente
    //printf("---------------------\n");
    //remove_cliente_byname(&clt,"Cliente1");
    //print_cliente(clt);

    //procurar cliente
    //printf("---------------------\n");
    //find_cliente_id(&clt,1);

    //Files
    //save_cliente_txt(clt,"../data/clientes.txt");
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //print_cliente(clt);
    //save_cliente_bin(clt,"../data/clientes.bin");
    //read_cliente_bin(&clt,"../data/clientes.bin");
    //print_cliente(clt);

}

void teste_viagens(){

    DATA dt1={20,11,2021};
    DATA dt2={21,11,2021};
    DATA dt3={22,11,2021};
    DATA dt4={23,11,2021};

    CLASSVIAGENS_DYNARRAY cidvis1={.name="Cidade1"};
    CLASSVIAGENS_DYNARRAY cidvis2={.name="Cidade2"};

    create_dynarray_classviagens(&viag,2);
    insert_viagens_dyn_array(&viag,&cidvis1,dt1,1,"Viagem1");
    insert_viagens_dyn_array(&viag,&cidvis2,dt2,2,"Viagem2");
    print_viagens_dyn_array(viag);

}

void teste_cidades(){

    char descricao_cidade1[]="Cidade Rural com cerca de mil habitantes e diversos pontos";
    char pontosInteresse_cidade1[]="Monumento1";

    insert_cidades_ordered(&cid,1,"Cidade1",descricao_cidade1,1.0f,0.0f,NULL);
    print_cidades(cid);

}