#ifndef PORTOPONTOS_STRUCTS_H
#define PORTOPONTOS_STRUCTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX100 100
#define MAX50 50
#define MAXCITIES 10

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

/*typedef struct pontos_interesse{
    char pontos[MAX50];   //array pontosInt interesse
}Pol;*/

typedef struct cidades{
    int ID;
    char *pnomecidade;
    char *descricao;           // array descricoes
    COORDENADAS coordenadas;
    char *pontosInt;    // lista pontosInt interesse
}CIDADES;

typedef struct classcidade{
    char nome[MAX100];
    CIDADES *pointercid;
    int totalcidades;       //size
}CLASSCIDADES_DYNARRAY;

////////////////////////     VIAGENS    ////////////////////////

typedef struct viagens{
    int id;
    char *pnomeviagem;
    char *cidades_a_visitar;   //ID's das cidades que cliente pretende visitar
    DATA dataviagem;
}VIAGENS;

typedef struct classviagens{
    char name[MAX100];
    VIAGENS *pointerviag;
    int totalviagens;   //size
}CLASSVIAGENS_DYNARRAY;

////////////////////////     CLIENTES    ////////////////////////

typedef struct historico_clientes{
    VIAGENS *viagem;
    //DATA data_inicio;
    DATA data_fim;
    //char *pontos;
    struct historico_clientes *pnext;
}H_Clientes;

typedef struct ll_historico_clientes{
    int nr_Historicos;
    H_Clientes *pointerhc;
}LL_H_Clientes;

typedef struct cliente{
    int id;
    char *nome;
    int NIF;
    char *email;
    LL_H_Clientes *hclientes;
    //VIAGENS viagens;    // array dinamico para registar viagens realizadas
    struct cliente *pnext; //LL clientes
}CLIENTE;

typedef struct classcliente{
    CLIENTE *pointerc;
    int totalclientes;
}CLASSCLIENTE;

#endif //PORTOPONTOS_STRUCTS_H
