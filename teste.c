#include "functions.h"
#include <stdio.h>

CLASSCLIENTE clt = {NULL, 0};
CLASSVIAGENS_DYNARRAY viag={NULL, 0};
CLASSCIDADES_DYNARRAY cid = {NULL, 0};

/**
 * insert_historico not working properly
 */
void teste_clientes(){

    //inserir cliente
    /*insert_cliente_ordered(&clt,"Cliente1",1,123456789,"client1@ufp.edu.pt",1);
    insert_cliente_ordered(&clt,"Cliente2",2,112345678,"client2@ufp.edu.pt",1);
    insert_cliente_ordered(&clt,"Cliente3",3,112233445,"client3@ufp.edu.pt",2);
    print_cliente(clt);*/

    //edit cliente
    /*read_clientes_txt(&clt,"../data/clientes.txt");
    edit_cliente(&clt,3,"Edit_cliente3",1221,"edit@gmail.com");
    print_cliente(clt);*/

    //remove cliente
    /*read_clientes_txt(&clt,"../data/clientes.txt");
    remove_cliente_byname(&clt,"Cliente3");
    //remove_cliente_byname(&clt,"Cliente1");
    print_cliente(clt);*/


    //print clientes orderByNif
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //print_clientes_orderByNif(clt);        //not working properly

    //Files
    //save_cliente_txt(clt,"../data/clientes.txt");
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //save_cliente_bin(clt,"../data/clientes.bin");
    //read_cliente_bin(&clt,"../data/clientes.bin");
    //print_cliente(clt);


    //historico                 - not working, Segmentation fault in insert_cliente
    /*DATA dt1={20,11,2021};
    DATA dt3={22,11,2021};
    read_clientes_txt(&clt,"../data/clientes.txt");
    read_viagens_txt(&clt,"../data/viagens.txt");

    insert_historico(&clt,2,"Viagem1",dt1,dt3);
    print_historico(clt,2);*/

}


void teste_viagens(){
    DATA dt1={20,11,2021};
    DATA dt2={21,11,2021};
    DATA dt3={22,11,2021};
    DATA dt4={31,11,2021};
    DATA dt5={02,11,2021};
    DATA newdt={8,1,2021};

    //inserir viagens
    //read_clientes_txt(&clt,"../data/clientes.txt");     //Insert + save_txt
    //insert_viagens_dyn_array(&clt,"Cliente1","Viagem1",dt1,1,5);
    //insert_viagens_dyn_array(&clt,"Cliente2","Viagem2",dt2,2,5);
    //insert_viagens_dyn_array(&clt,"Cliente3","Viagem3",dt3,3,5);
    //insert_viagens_dyn_array(&clt,"Cliente3","Viagem4",dt4,4,5);
    //print_viagens(clt);
    //save_viagens_txt(clt,"../data/viagens.txt");
    //free_dynarray_classviagens(&clt);*/

    //Edit info de viagem (muda cidades e data) | id não muda porque tratamos como serial
    /*read_clientes_txt(&clt,"../data/clientes.txt");
    read_viagens_txt(&clt,"../data/viagens.txt");
    edit_viagens(clt,"Ruben",5,"Portugal",newdt);
    print_viagens(clt);
    free_dynarray_classviagens(&clt);*/

    //Remove viagens
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //read_viagens_txt(&clt,"../data/viagens.txt");
    //remove_viagem_byid(&clt,"Cliente3",3);
    //print_viagens(clt);
    //free_dynarray_classviagens(&clt);


    //Files
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //read_viagens_txt(&clt,"../data/viagens.txt");
    //save_viagens_bin(clt,"../data/viagens.bin");
    //read_viagens_bin(&clt,"../data/viagens.bin");
    //print_viagens(clt);

    //relatorio viagens
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //read_viagens_txt(&clt,"../data/viagens.txt");
    //read_cidades_txt(&clt,"../data/cidades.txt");
    //print_relatorio_viagens_cidades_dateX(&clt, "Cliente3", dt4);
    //print_relatorio_viagem_cidadeX(&clt,"Cliente3","Cidade17");
    //print_relatorio_viagem_PolX(&clt,"Cliente3","PontosInteresse_cidade20");

}


void teste_cidades(){

    char descricao_cidade1[]="Descricao Cidade1";
    char descricao_cidade2[]="Descricao Cidade2";
    char nova_desc1[]="Nova descricao";


    //inserir cidades
    /*read_clientes_txt(&clt,"../data/clientes.txt");
    read_viagens_txt(&clt,"../data/viagens.txt");
    insert_cidade_dynarray(&clt,"Viagem1","Cidade1",1,descricao_cidade1,1.0f,1.0f);
    insert_cidade_dynarray(&clt,"Viagem1","Cidade2",2,descricao_cidade2,2.0f,2.0f);
    insert_cidade_dynarray(&clt,"Viagem1","Cidade3",3,"Descricao Cidade3",3.0f,3.0f);
    insert_cidade_dynarray(&clt,"Viagem1","Cidade4",4,"Descricao Cidade4",4.0f,4.0f);
    insert_cidade_dynarray(&clt,"Viagem1","Cidade5",5,"Descricao Cidade5",5.0f,5.0f);
    insert_pol_cidade(&clt,1,"PontosInteresse_cidade1");
    insert_pol_cidade(&clt,2,"PontosInteresse_cidade2");
    insert_pol_cidade(&clt,3,"PontosInteresse_cidade3");
    insert_pol_cidade(&clt,4,"PontosInteresse_cidade4");
    insert_pol_cidade(&clt,5,"PontosInteresse_cidade5");
    //print_cidades(clt);

    insert_cidade_dynarray(&clt,"Viagem2","Cidade6",6,"Descricao Cidade6",6.0f,6.0f);
    insert_cidade_dynarray(&clt,"Viagem2","Cidade7",7,"Descricao Cidade7",7.0f,7.0f);
    insert_cidade_dynarray(&clt,"Viagem2","Cidade8",8,"Descricao Cidade8",8.0f,8.0f);
    insert_cidade_dynarray(&clt,"Viagem2","Cidade9",9,"Descricao Cidade9",9.0f,9.0f);
    insert_cidade_dynarray(&clt,"Viagem2","Cidade10",10,"Descricao Cidade10",10.0f,10.0f);
    insert_pol_cidade(&clt,6,"PontosInteresse_cidade6");
    insert_pol_cidade(&clt,7,"PontosInteresse_cidade7");
    insert_pol_cidade(&clt,8,"PontosInteresse_cidade8");
    insert_pol_cidade(&clt,9,"PontosInteresse_cidade9");
    insert_pol_cidade(&clt,10,"PontosInteresse_cidade10");
    //print_cidades(clt);

    insert_cidade_dynarray(&clt,"Viagem3","Cidade11",11,"Descricao Cidade11",11.0f,11.0f);
    insert_cidade_dynarray(&clt,"Viagem3","Cidade12",12,"Descricao Cidade12",12.0f,12.0f);
    insert_cidade_dynarray(&clt,"Viagem3","Cidade13",13,"Descricao Cidade13",13.0f,13.0f);
    insert_cidade_dynarray(&clt,"Viagem3","Cidade14",14,"Descricao Cidade14",14.0f,14.0f);
    insert_cidade_dynarray(&clt,"Viagem3","Cidade15",15,"Descricao Cidade15",15.0f,15.0f);
    insert_pol_cidade(&clt,11,"PontosInteresse_cidade11");
    insert_pol_cidade(&clt,12,"PontosInteresse_cidade12");
    insert_pol_cidade(&clt,13,"PontosInteresse_cidade13");
    insert_pol_cidade(&clt,14,"PontosInteresse_cidade14");
    insert_pol_cidade(&clt,15,"PontosInteresse_cidade15");
    //print_cidades(clt);

    //Viagem 4 pertence ao mesmo cliente da Viagem3 (Cliente3)
    insert_cidade_dynarray(&clt,"Viagem4","Cidade16",16,"Descricao Cidade16",16.0f,16.0f);
    insert_cidade_dynarray(&clt,"Viagem4","Cidade17",17,"Descricao Cidade17",17.0f,17.0f);
    insert_cidade_dynarray(&clt,"Viagem4","Cidade18",18,"Descricao Cidade18",18.0f,18.0f);
    insert_cidade_dynarray(&clt,"Viagem4","Cidade19",19,"Descricao Cidade19",19.0f,19.0f);
    insert_cidade_dynarray(&clt,"Viagem4","Cidade20",20,"Descricao Cidade20",20.0f,20.0f);
    insert_pol_cidade(&clt,16,"PontosInteresse_cidade16");
    insert_pol_cidade(&clt,17,"PontosInteresse_cidade17");
    insert_pol_cidade(&clt,18,"PontosInteresse_cidade18");
    insert_pol_cidade(&clt,19,"PontosInteresse_cidade19");
    insert_pol_cidade(&clt,20,"PontosInteresse_cidade20");
    print_cidades(clt);
    //free_dynarray_classcidades(&clt);*/


    //edit cidades
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //read_viagens_txt(&clt,"../data/viagens.txt");
    //read_cidades_txt(&clt,"../data/cidades.txt");
    //edit_cidades(clt,"Viagem4",19,"Cidade14edit","nova_desc14",0.0f,0.0f);
    //print_cidades(clt);
    //free_dynarray_classcidades(&clt);*/


    //remove cidades
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //read_viagens_txt(&clt,"../data/viagens.txt");
    //read_cidades_txt(&clt,"../data/cidades.txt");
    //remove_cidade_id(&clt,"Viagem1",1);
    //remove_cidade_id(&clt,"Viagem2",10);    //errors deletes next viagem 1st cidade too
    //print_cidades(clt);
    //free_dynarray_classcidades(&clt);*/


    //Files txt
    //save_cidades_txt(clt,"../data/cidades.txt");
    //read_clientes_txt(&clt,"../data/clientes.txt");
    //read_viagens_txt(&clt,"../data/viagens.txt");
    //read_cidades_txt(&clt,"../data/cidades.txt");
    //print_cidades(clt);
    //find_pol_cidade(&clt,6);


    //Files bin
    read_clientes_txt(&clt,"../data/clientes.txt");
    read_viagens_txt(&clt,"../data/viagens.txt");
    read_cidades_txt(&clt,"../data/cidades.txt");
    //save_cidades_bin(clt,"../data/cidades.bin");
    //read_cidades_bin(&clt,"../data/cidades.bin");    //Errors when inserting pol_into_cidade
    //print_cidades(clt);


}