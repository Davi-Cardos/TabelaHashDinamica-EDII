#include "cliente.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime cliente
void imprime(Cliente *cliente) {
    printf("**********************************************\n");
    printf("Cliente de código ");
    printf("%d\n", cliente->codCliente);
    printf("Nome: ");
    printf("%s\n", cliente->nome);
    printf("Data de Nascimento: ");
    printf("%s\n", cliente->data_nascimento);
}

// Cria cliente. Lembrar de usar free(func)
Cliente *cliente(int cod, char *nome, char *data_nascimento) {
    Cliente *cliente = (Cliente *) malloc(sizeof(Cliente));
    //inicializa espaço de memória com ZEROS
    if (cliente) memset(cliente, 0, sizeof(Cliente));
    //copia valores para os campos de cliente
    cliente->codCliente = cod;
    strcpy(cliente->nome, nome);
    strcpy(cliente->data_nascimento, data_nascimento);
    return cliente;
}

// Salva cliente no arquivo out, na posicao atual do cursor
void salva(Cliente *cliente, FILE *out) {
    fwrite(&cliente->codCliente, sizeof(int), 1, out);
    //cliente->nome ao invés de &cliente->nome, pois string já é ponteiro
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
    fwrite(cliente->data_nascimento, sizeof(char), sizeof(cliente->data_nascimento), out);
}

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
Cliente *le(FILE *in) {
    Cliente *func = (Cliente *) malloc(sizeof(Cliente));
    if (0 >= fread(&func->codCliente, sizeof(int), 1, in)) {
	free(func);
	return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    return func;
}

// Retorna tamanho do funcionario em bytes
int tamanho() {
    return sizeof(int)  //cod
            + sizeof(char) * 50 //nome
            + sizeof(char) * 20; //data_nascimento
}

