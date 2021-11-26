#ifndef PORTOPONTOS_FUNCTIONS_H
#define PORTOPONTOS_FUNCTIONS_H
#include "structs.h"

/////////////////////////////////     Clientes    /////////////////////////////////
void insert_cliente_ordered(CLASSCLIENTE *pcs, char name[], int id, int NIF, char email[]);
void print_cliente(CLASSCLIENTE pcs);
void remove_cliente_byname(CLASSCLIENTE *pcs, char name[]);
CLIENTE *find_cliente_id(CLASSCLIENTE *pcs, int id);
//Files
void save_cliente_txt(CLASSCLIENTE pcs, char filename[]);
void read_clientes_txt(CLASSCLIENTE *pcs, char filename[]);
void save_cliente_bin(CLASSCLIENTE pcs, char filename[]);
void read_cliente_bin(CLASSCLIENTE *pcs, char filename[]);                  //####

CLIENTE *find_historico_cidade(CLASSCLIENTE *pcs,H_Clientes hist,CIDADES cidade); //###
CLIENTE *find_historico_pol(CLASSCLIENTE *pcs,H_Clientes hist);                   //###


/////////////////////////////////     Viagens     /////////////////////////////////
void insert_viagens_dyn_array(CLASSVIAGENS *pcs,CIDADES cidadesvisitada[],DATA date,int id,char nomeviag[]);
void edit_viagens(VIAGENS *pcs,int id,DATA date);                                 //###
void remove_viagens(VIAGENS *pcs,int id);
void print_viagens_dyn_array(CLASSVIAGENS pcs);
//Files
void save_viagens_txt(CLASSVIAGENS pcs, char filename[]);
void read_viagens_txt(CLASSVIAGENS *pcs, char filename[]);
void save_viagens_bin(CLASSVIAGENS pcs, char filename[]);
void read_viagens_bin(CLASSVIAGENS *pcs, char filename[]);

void relatorio(DYN_ARRAY_VIAGENS *viag,CLASSCLIENTE *cli, DATA d1, DATA d2);


/////////////////////////////////    Cidades     /////////////////////////////////
void insert_cidades_ordered(CLASSCIDADES *pcs,int id,char name[],char desc[],float latitude,float longitude,Pol pontosInt[]);
void edit_cidades(CLASSCIDADES *pcs,int id,int name,char novadesc,float x,float y,char pontos[]);
void remove_cidades_nome(CLASSCIDADES *pcs,char nome[]);
void print_cidades(CLASSCIDADES pcs);
CIDADES * find_cidade_nome(CLASSCIDADES pcs,char nome[]);
CIDADES * find_cidade_ID(CLASSCIDADES pcs, int id);
CIDADES * edit_descricao_cidade(CLASSCIDADES *pcs,char newdesc);

//CIDADES *find_cidade_descricao(CLASSCIDADES *pcs,int id,char desc);

//Files
void save_cidades_txt(CLASSCIDADES pcs, char filename[]);
void read_cidades_txt(CLASSCIDADES *pcs, char filename[]);
void save_cidades_bin(CLASSCIDADES pcs, char filename[]);
void read_cidades_bin(CLASSCIDADES *pcs, char filename[]);

Pol *create_pol(CIDADES *pcs,int id,Pol pol);
Pol *remove_pol(CIDADES *pcs,int id,Pol pol);
Pol *find_pol(CIDADES *pcs,int id,Pol pol);




// Testes
void teste_clientes();
void teste_viagens();
void teste_cidades();

#endif //PORTOPONTOS_FUNCTIONS_H