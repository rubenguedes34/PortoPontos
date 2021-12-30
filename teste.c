#include "functions.h"
#include <stdio.h>

CLASSCLIENTE clt = { NULL, 0};
CLASSVIAGENS_DYNARRAY viag={"Viagens",NULL,0};
CLASSCIDADES_DYNARRAY cid = {"Cidades",NULL,0};

void teste_clientes(){

    //inserir cliente
    /*insert_cliente_ordered(&clt,"Ruben",1,232928185,"ruben@ufp.edu.pt");
    insert_cliente_ordered(&clt,"Cliente1",2,123456789,"client1@ufp.edu.pt");
    insert_cliente_ordered(&clt,"Cliente2",3,112345678,"client2@ufp.edu.pt");
    insert_cliente_ordered(&clt,"Cliente3",4,111234567,"client3@ufp.edu.pt");
    print_cliente(clt); */

    //remoção cliente
    //printf("---------------------\n");
    //remove_cliente_byname(&clt,"Cliente1");
    //print_cliente(clt);


    //Files
    //save_cliente_txt(clt,"../data/clientes.txt");
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //print_cliente(clt);
    //save_cliente_bin(clt,"../data/clientes.bin");
    //read_cliente_bin(&clt,"../data/clientes.bin");
    //print_cliente(clt);

    //historico
    DATA dt1={20,11,2021};
    DATA dt3={22,11,2021};
    VIAGENS viagem1={1,"Viagem1","0 1 2 3 4 5",dt1};
    insert_historico(&clt,1,&viagem1,dt3);
    print_historico(clt,1);

}

void teste_viagens(){

    DATA dt1={20,11,2021};
    DATA dt2={21,11,2021};
    DATA dt3={22,11,2021};

    //create_dynarray_classviagens(&viag,2);
    //insert_viagens_dyn_array(&viag,"Viagem1","0 1 2 3 4 5",dt1,1);
    //insert_viagens_dyn_array(&viag,"Viagem2","0 2 3 1 5 4",dt2,2);
    //print_viagens_dyn_array(viag);
    //edit_viagens(&viag,"Viagem1","5 4 3 2 1 0",dt3);
    //print_viagens_dyn_array(viag);
    //remove_viagem_byid(&viag,1);
    //print_viagens_dyn_array(viag);
    //free_dynarray_classviagens(&viag);

    //Files
    //save_viagens_txt(viag,"../data/viagens.txt");
    //read_viagens_txt(&viag,"../data/viagens.txt");
    //print_viagens_dyn_array(viag);
    //save_viagens_bin(viag,"../data/viagens.bin");
    read_cidades_bin(&viag,"../data/viagens.bin");
    print_viagens_dyn_array(viag);

}

void teste_cidades(){

    char descricao_cidade1[]="Descricao Cidade1";
    char descricao_cidade2[]="Descricao Cidade2";
    char nova_desc1[]="Nova descricao";
    char pontos_cidade1[]="Pontos1",pontos_cidade2[]="Pontos2";

    //create_dynarray_classcidades(&cid,2);
    //insert_cidade_dynarray(&cid,"Cidade1",1,descricao_cidade1,2.0f,2.0f,pontos_cidade1);
    //insert_cidade_dynarray(&cid,"Cidade2",2,descricao_cidade2,1.0f,0.0f,pontos_cidade2);
    //print_dynarray_classcidades(cid);
    //edit_cidades(&cid,"Cidade1",nova_desc1,1.1f,1.1f,pontosInteresse_cidade2);
    //print_dynarray_classcidades(cid);
    //free_dynarray_classcidades(&cid);


    //Files
    //save_cidades_txt(cid,"../data/cidades.txt");
    //read_cidades_txt(&cid,"../data/cidades.txt");
    //print_dynarray_classcidades(cid);
    //save_cidades_bin(cid,"../data/cidades.bin");
    read_cidades_bin(&cid,"../data/cidades.bin");
    print_dynarray_classcidades(cid);




}