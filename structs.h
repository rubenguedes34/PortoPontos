#ifndef PORTOPONTOS_STRUCTS_H
#define PORTOPONTOS_STRUCTS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX200 200

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
    char *pontos;   //array pontos interesse
}Pol;

typedef struct cidades{
    int ID;
    char *nome;
    char *descricao;
    COORDENADAS coordenadas;
    Pol *pontosInteresse;    // lista pontos interesse
    struct cidades *pnext;
}CIDADES;

typedef struct classcidade{
    CIDADES *pointercid;
    int totalcidades;
}CLASSCIDADES;

////////////////////////     VIAGENS    ////////////////////////

typedef struct viagens{
    int id;
    char *pnomeviagem;
    CIDADES cidades;
    DATA dataviagem;
    //struct viagens *pnext;
}VIAGENS;

typedef struct classviagens{
    char name[MAX200];
    VIAGENS *pointerviag;
    int totalviagens;   //size
    int current_viagem;
    int *viagens_realizadas;
    int *viagens_porRealizar;
}CLASSVIAGENS_DYNARRAY;

////////////////////////     CLIENTES    ////////////////////////

typedef struct historico_clientes{
    VIAGENS viagens;
    DATA data_inicio;
    DATA data_fim;
    Pol pontos;
}H_Clientes;

typedef struct cliente{
    int id;
    char *nome;
    int NIF;
    char *email;
    H_Clientes hclientes;
    struct cliente *pnext; //LL clientes
}CLIENTE;

typedef struct classcliente{
    CLIENTE *pointerc;
    int totalclientes;
}CLASSCLIENTE;

#endif //PORTOPONTOS_STRUCTS_H
