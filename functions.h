#ifndef PORTOPONTOS_FUNCTIONS_H
#define PORTOPONTOS_FUNCTIONS_H
#include "structs.h"

/////////////////////////////////     Clientes    /////////////////////////////////

void create_dynarray_classcidades(CLASSCIDADES_DYNARRAY *pcc, int initsize);
void insert_cliente_ordered(CLASSCLIENTE *pcs, char name[], int id, int NIF, char email[]);
void print_cliente(CLASSCLIENTE pcs);
void remove_cliente_byname(CLASSCLIENTE *pcs, char name[]);
CLIENTE *find_cliente_id(CLASSCLIENTE *pcs, int id);

//Files
void save_cliente_txt(CLASSCLIENTE pcs, char filename[]);
void read_clientes_txt(CLASSCLIENTE *pcs, char filename[]);
void save_cliente_bin(CLASSCLIENTE pcs, char filename[]);
void read_cliente_bin(CLASSCLIENTE *pcs, char filename[]);

CLIENTE *find_historico_cidade(CLASSCLIENTE *pcs,H_Clientes hist,CIDADES cidade); //###
CLIENTE *find_historico_pol(CLASSCLIENTE *pcs,H_Clientes hist);                   //###

void insert_historico(CLASSCLIENTE *pcl, int id_cliente, VIAGENS viagem_realizada[], DATA d_fim);
void print_historico(CLASSCLIENTE cc, int id_cliente);

/////////////////////////////////     Viagens     /////////////////////////////////

void create_dynarray_classviagens(CLASSVIAGENS_DYNARRAY *pcv, int init_size);
void insert_viagens_dyn_array(CLASSVIAGENS_DYNARRAY *pcv, char nomeviag[],char cidadesvisitadas[], DATA date, int id_viagem);
void edit_viagens(CLASSVIAGENS_DYNARRAY *pcv, char name[], char cidades[], DATA date);
void print_viagens_dyn_array(CLASSVIAGENS_DYNARRAY pcv);

VIAGENS * find_viagem_nome(CLASSVIAGENS_DYNARRAY cv, char name[]);
VIAGENS * find_viagem_id(CLASSVIAGENS_DYNARRAY cv, int id);
void remove_viagem_byid(CLASSVIAGENS_DYNARRAY *pcv, int id);
void free_dynarray_classviagens(CLASSVIAGENS_DYNARRAY *pcv);


//Files
void save_viagens_txt(CLASSVIAGENS_DYNARRAY pcv, char filename[]);
void read_viagens_txt(CLASSVIAGENS_DYNARRAY *pcs, char filename[]);
void save_viagens_bin(CLASSVIAGENS_DYNARRAY pcs, char filename[]);
void read_viagens_bin(CLASSVIAGENS_DYNARRAY *pcs, char filename[]);

//void relatorio(DYN_ARRAY_VIAGENS *viag,CLASSCLIENTE *cli, DATA d1, DATA d2);


/////////////////////////////////    Cidades     /////////////////////////////////

void create_dynarray_classcidades(CLASSCIDADES_DYNARRAY *pcc, int initsize);
void insert_cidade_dynarray(CLASSCIDADES_DYNARRAY *pcc, char name[], int id, char desc[], float latitude, float longitude, char pontos[]);
void edit_cidades(CLASSCIDADES_DYNARRAY *pcc, char nome[], char novadesc[], float x, float y, char pontos[]);
void remove_cidade_id(CLASSCIDADES_DYNARRAY *pcs, int id);
void print_dynarray_classcidades(CLASSCIDADES_DYNARRAY pcc);
CIDADES * find_cidade_nome(CLASSCIDADES_DYNARRAY pcs, char nome[]);
CIDADES * find_cidade_ID(CLASSCIDADES_DYNARRAY pcs, int id);
//CIDADES * edit_descricao_cidade(CLASSCIDADES_DYNARRAY *pcs, char *newdesc);
void free_dynarray_classcidades(CLASSCIDADES_DYNARRAY *pcs);

//CIDADES *find_cidade_descricao(CLASSCIDADES_DYNARRAY *pcs,int id,char desc);

//Files
void save_cidades_txt(CLASSCIDADES_DYNARRAY pcs, char filename[]);
void read_cidades_txt(CLASSCIDADES_DYNARRAY *pcs, char filename[]);
void save_cidades_bin(CLASSCIDADES_DYNARRAY pcs, char filename[]);
void read_cidades_bin(CLASSCIDADES_DYNARRAY *pcs, char filename[]);




// Testes
void teste_clientes();
void teste_viagens();
void teste_cidades();

#endif //PORTOPONTOS_FUNCTIONS_H