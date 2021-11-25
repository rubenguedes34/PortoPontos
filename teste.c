#include "functions.h"
#include <stdio.h>

CLASSCLIENTE clt = { NULL, 0};
CLASSVIAGENS viag = {NULL,0};

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

    CIDADES C0 = {.ID=0, .coordenadas.x=1.0, .coordenadas.y=0.0};
    CIDADES C1 = {.ID=1, .coordenadas.x=1.0, .coordenadas.y=1.0};
    CIDADES C2 = {.ID=2, .coordenadas.x=2.0, .coordenadas.y=1.0};
    CIDADES C3 = {.ID=3, .coordenadas.x=2.0, .coordenadas.y=0.0};
    CIDADES C4 = {.ID=4, .coordenadas.x=3.0, .coordenadas.y=0.0};
    CIDADES C5 = {.ID=5, .coordenadas.x=4.0, .coordenadas.y=1.0};

    VIAGENS T0 = {.id=0, .cidades={0, 1, 2, 3, 4, 5}};
    VIAGENS T1 = {.id=1, .cidades={0, 2, 3, 1, 5, 4}};    // Populacao inicial

    //insert_viagens_dyn_array(&viag,&T1,dt1,1,"viagem1",1);
    //print_viagens_dyn_array(viag);

}

void teste_cidades(){

}