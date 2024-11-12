#ifndef ADDCLIENTES_H
#define ADDCLIENTES_H

#include <stdlib.h>
#include <stdio.h>

#define QTD_CLIENTES 50

void insere_clientes(FILE* out) {
    printf("Inserindo %d clientes no arquivo...\n", QTD_CLIENTES);


    char* nomes[50] = {
   "João", "Maria", "Pedro", "Ana", "Paulo", "Carla", "Ricardo", "Fernanda",
   "Lucas", "Juliana", "Leonardo", "Bianca", "Felipe", "Camila", "Bruno",
   "Mariana", "Thiago", "Eduarda", "André", "Letícia", "Rodrigo", "Patrícia",
   "Sérgio", "Cristina", "Maurício", "Vera", "Vinícius", "Sabrina", "Rafael",
   "Marta", "Guilherme", "Natália", "Daniel", "Larissa", "Rogério", "Isabela",
   "Gustavo", "Caroline", "Fábio", "Aline", "Marcelo", "Roberta", "Alexandre",
   "Renata", "Diego", "Lúcia", "Roberto", "Flávia", "Antônio", "Helena"
    };

    // Vetor com 50 IDs fora de ordem
    int codClientes[50] = {
        35, 3, 27, 49, 12, 7, 18, 50, 42, 15,
        1, 31, 19, 23, 9, 24, 4, 36, 46, 14,
        22, 10, 32, 30, 43, 11, 16, 48, 26, 20,
        34, 21, 45, 38, 13, 17, 47, 6, 25, 5,
        2, 28, 39, 29, 44, 40, 41, 33, 8, 37
    };



#endif