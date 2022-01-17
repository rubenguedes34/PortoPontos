#ifndef PORTOPONTOS_FUNCTIONS_H
#define PORTOPONTOS_FUNCTIONS_H
#include "structs.h"

///////////////////////////////////////////////    Clientes    ///////////////////////////////////////////////

void insert_cliente_ordered(CLASSCLIENTE *pcc, char name[], int id, int NIF, char email[], int viagens);
void print_cliente(CLASSCLIENTE pcc);
void edit_cliente(CLASSCLIENTE *pcl, int id, char novonome[], int new_nif, char new_email[]);
void remove_cliente_byname(CLASSCLIENTE *pcc, char name[]);
CLIENTE *find_cliente_nif(CLASSCLIENTE *pcc, int NIF);
CLIENTE *find_cliente_nome(CLASSCLIENTE *pcc,char nome[]);
void print_clientes_orderByNif(CLASSCLIENTE cc);    //###

//Files
void save_cliente_txt(CLASSCLIENTE pcl, char filename[]);
void read_clientes_txt(CLASSCLIENTE *pcl, char filename[]);
void save_cliente_bin(CLASSCLIENTE pcl, char filename[]);
void read_cliente_bin(CLASSCLIENTE *pcl, char filename[]);

void insert_historico(CLASSCLIENTE *pcc, int id_cliente, char nome_viagem[], DATA d_inicio, DATA d_fim);    //###
void print_historico(CLASSCLIENTE cc, int id_cliente);  //###


///////////////////////////////////////////////    Viagens     ///////////////////////////////////////////////


void create_dynarray_classviagens(CLIENTE *pcl, int init_size);
void insert_viagens_dyn_array(CLASSCLIENTE *pcl,char nome_cliente[], char nomeviag[], DATA date, int id_viagem, int cidades);
void edit_viagens(CLASSCLIENTE pcc, char nome_cliente[], int id_viagem, char new_name[], DATA new_date);
void print_viagens(CLASSCLIENTE pcl);

VIAGENS * find_viagem_nome(CLASSCLIENTE pcc, char name[]);
VIAGENS * find_viagem_id(CLASSCLIENTE pcc, int id);
void remove_viagem_byid(CLASSCLIENTE *pcl, char name[], int id_viagem);
void free_dynarray_classviagens(CLASSCLIENTE *pcc);

//Files
void save_viagens_txt(CLASSCLIENTE pcl, char filename[]);
void read_viagens_txt(CLASSCLIENTE *pcl, char filename[]);
void save_viagens_bin(CLASSCLIENTE cc, char filename[]);
void read_viagens_bin(CLASSCLIENTE *pcs, char filename[]);

int date_cmp(DATA dt1, DATA dt2);
void print_relatorio_viagens_cidades_dateX(CLASSCLIENTE *pcl, char nome_cliente[], DATA date);
void print_relatorio_viagem_cidadeX(CLASSCLIENTE *pcl, char nome_cliente[], char nome_cidade[]);
void print_relatorio_viagem_PolX(CLASSCLIENTE *pcl, char nome_cliente[], char local_visitado[]);


///////////////////////////////////////////////    Cidades     ///////////////////////////////////////////////


void create_dynarray_classcidades(VIAGENS *pv, int initsize);
void insert_cidade_dynarray(CLASSCLIENTE *pcl, char viagem[], char name[], int id, char desc[], float latitude, float longitude);
void edit_cidades(CLASSCLIENTE pcc, char nome_viagem[],int id_cidade, char new_name[], char new_desc[], float latit, float longi);
void remove_cidade_id(CLASSCLIENTE *pcc,char nome_viagem[], int id_cidade);
void print_cidades(CLASSCLIENTE cc);
void free_dynarray_classcidades(CLASSCLIENTE *pcc);

CIDADES * find_cidade_nome(CLASSCLIENTE cc, char nome[]);
CIDADES * find_cidade_ID(CLASSCLIENTE *pcc, int id);


void create_pol(CIDADES *pc, int size);
void insert_pol_cidade(CLASSCLIENTE *pcc,int id_cidade, char pontos[]);
Pol * find_pol_cidade(CLASSCLIENTE *pcl, int id_cidade);
void remove_pol(CLASSCLIENTE *pcl, int id_pol);                                   //###

CIDADES *find_historico_cidade(CLASSCLIENTE *pcs,H_Clientes hist,CIDADES cidade); //###
CIDADES *find_historico_pol(CLASSCLIENTE *pcs,H_Clientes hist);                   //###

//Files
void save_cidades_txt(CLASSCLIENTE cc, char filename[]);
void read_cidades_txt(CLASSCLIENTE *pcc, char filename[]);
void save_cidades_bin(CLASSCLIENTE cc, char filename[]);
void read_cidades_bin(CLASSCLIENTE *pcc, char filename[]);


/////////////////////////////////

// Testes
void teste_clientes();
void teste_viagens();
void teste_cidades();

#endif //PORTOPONTOS_FUNCTIONS_H