#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int codCliente;
    char nome[100];
} CLIENTE;

// Imprime Cliente
void imprime(CLIENTE* func);

// Cria Cliente. Lembrar de usar free(CLIENTE)
CLIENTE* Cliente(int cod, char* nome);

// Le um CLIENTE do arquivo in na posicao atual do cursor
// Retorna um ponteiro para CLIENTE lido do arquivo
CLIENTE* le(FILE* in);

// Retorna tamanho do CLIENTE em bytes
int tamanho();

#endif