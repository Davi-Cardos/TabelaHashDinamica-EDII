#ifndef ADDCLIENTES_H
#define ADDCLIENTES_H

#include <stdlib.h>
#include <stdio.h>

#define QTD_CLIENTES 15

void insere_clientes(FILE* out) {
    printf("Inserindo %d clientes no arquivo...\n", QTD_CLIENTES);


    char* nomes[15] = {
   "João", "Maria", "Pedro", "Ana", "Paulo", "Carla", "Ricardo", "Fernanda",
   "Lucas", "Juliana", "Leonardo", "Bianca", "Felipe", "Camila", "Bruno"

    };


    int codClientes[15] = {
        35, 3, 27, 49, 12, 7, 18, 50, 42, 15,
         1, 31, 19, 23, 9 
    };

    CLIENTE * novo_cliente;

      for (int i = 0; i < QTD_CLIENTES; i++) {
        novo_cliente = Cliente(codClientes[i], nomes[i]);
        salva(novo_cliente, out);
        free(novo_cliente);
    }

}

void le_clientes(FILE* in) {
    printf("\n\nLendo funcionários do arquivo...\n\n");
    rewind(in);
    CLIENTE* f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}





#endif