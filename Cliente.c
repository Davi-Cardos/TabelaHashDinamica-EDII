#include "Cliente.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime cliente
void imprime(CLIENTE *cliente) {
    printf("**********************************************\n");
    printf("Cliente de código ");
    printf("%d\n", cliente->codCliente);
    printf("Nome: ");
    printf("%s\n", cliente->nome);
}


void salva(CLIENTE *cliente, FILE *out) {
    fwrite(&cliente->codCliente, sizeof(int), 1, out);
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
}

// Cria cliente. Lembrar de usar free(func)
CLIENTE *Cliente(int cod, char *nome) {
    CLIENTE *cliente = (CLIENTE *) malloc(sizeof(CLIENTE));
    //inicializa espaço de memória com ZEROS
    if (cliente) memset(cliente, 0, sizeof(Cliente));
    //copia valores para os campos de cliente
    cliente->codCliente = cod;
    strcpy(cliente->nome, nome);
    return cliente;
}


// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
CLIENTE *le(FILE *in) {
    CLIENTE *func = (CLIENTE *) malloc(sizeof(CLIENTE));
    if (0 >= fread(&func->codCliente, sizeof(int), 1, in)) {
	free(func);
	return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    return func;
}

// Retorna tamanho do funcionario em bytes
int tamanho() {
    return sizeof(int)  //cod 
    + sizeof(char) * 50; //nome
}

