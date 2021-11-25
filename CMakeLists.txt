cmake_minimum_required(VERSION 3.15)
project(PortoPontos C)

set(CMAKE_C_STANDARD 99)

add_executable(PortoPontos main.c structs.h functions.c functions.h GenericAlgorithm.c GenericAlgorithm.h teste.c clientes.c viagens.c cidades.c)