#ifndef PORTOPONTOS_STRUCTS_H
#define PORTOPONTOS_STRUCTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX100 100

typedef struct data{
    int dia;
    int mes;
    int ano;
}DATA;

typedef struct coordenadas{
    float x;
    float y;
}COORDENADAS;

////////////////////////     CIDADES    ////////////////////////

typedef struct pontos_interesse{
    int id_cid;
    char *nome_local;
}Pol;

typedef struct ll_pol{
    Pol *ppol;
    int n_pontos;
    int totalpontos;
}Pol_dynarray;

typedef struct cidades{
    int ID;
    char *nomecidade;
    char *descricao;
    COORDENADAS coordenadas;
    Pol_dynarray pontosInt;       //pointer para Pol
}CIDADES;

typedef struct classcidade{
    CIDADES *pointercid;
    int n_cidades;      // cidades visitadas
    int totalcidades;       //size array
}CLASSCIDADES_DYNARRAY;

////////////////////////     VIAGENS    ////////////////////////

typedef struct viagens{
    int id;
    char *nomeviagem;
    DATA dataviagem;
    CLASSCIDADES_DYNARRAY cidades_visitadas;
}VIAGENS;

typedef struct classviagens{
    VIAGENS *pointerviag;
    int n_viagens;      // viagens realizadas
    int totalviagens;   //size array
}CLASSVIAGENS_DYNARRAY;

////////////////////////     CLIENTES    ////////////////////////

typedef struct historico_clientes{
    char *nome_viagem;
    DATA data_inicio;
    DATA data_fim;
    struct historico_clientes *pnext;
}H_Clientes;

typedef struct ll_historico_clientes{
    int nr_historico;
    H_Clientes *pointerhc;
}LL_H_Clientes;

typedef struct cliente{
    int id;
    char *nome;
    int NIF;
    char *email;
    CLASSVIAGENS_DYNARRAY viagens;        //viagens realizadas por cada cliente
    LL_H_Clientes *hclientes;
    struct cliente *pnext;
}CLIENTE;

typedef struct classcliente{
    CLIENTE *pointerc;
    int totalclientes;
}CLASSCLIENTE;

#endif //PORTOPONTOS_STRUCTS_H