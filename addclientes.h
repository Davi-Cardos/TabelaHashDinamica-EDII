#ifndef ADDCLIENTES_H
#define ADDCLIENTES_H

#include <stdlib.h>
#include <stdio.h>

#define QTD_CLIENTES 50

void insere_clientes(FILE* out) {
    printf("Inserindo %d clientes no arquivo...\n", QTD_CLIENTES);

    Cliente* clientes[QTD_CLIENTES];


    char* nomes[50] = {
   "João", "Maria", "Pedro", "Ana", "Paulo", "Carla", "Ricardo", "Fernanda",
   "Lucas", "Juliana", "Leonardo", "Bianca", "Felipe", "Camila", "Bruno",
   "Mariana", "Thiago", "Eduarda", "André", "Letícia", "Rodrigo", "Patrícia",
   "Sérgio", "Cristina", "Maurício", "Vera", "Vinícius", "Sabrina", "Rafael",
   "Marta", "Guilherme", "Natália", "Daniel", "Larissa", "Rogério", "Isabela",
   "Gustavo", "Caroline", "Fábio", "Aline", "Marcelo", "Roberta", "Alexandre",
   "Renata", "Diego", "Lúcia", "Roberto", "Flávia", "Antônio", "Helena"
    };

    // Vetor com 50 datas de nascimento
    char* datas[50] = {
        "01/01/1990", "15/05/1985", "22/09/1975", "30/12/1999", "14/07/1965",
        "08/03/1983", "19/11/1978", "28/02/1991", "05/06/1980", "17/09/1995",
        "25/01/1984", "02/11/1992", "06/08/1987", "13/03/1974", "20/10/1989",
        "24/04/1986", "09/05/1993", "21/07/1990", "18/02/1981", "11/06/1982",
        "29/12/1970", "04/11/1996", "26/09/1979", "03/08/1988", "10/03/1980",
        "12/12/1973", "07/04/1991", "16/07/1982", "27/10/1985", "23/06/1978",
        "09/12/1994", "01/05/1987", "14/02/1983", "05/09/1976", "11/11/1995",
        "25/08/1998", "08/07/1993", "13/12/1990", "20/04/1981", "29/03/1979",
        "07/11/1997", "19/01/1988", "03/06/1972", "17/10/1980", "21/03/1986",
        "14/08/1999", "28/01/1977", "02/04/1990", "18/11/1984", "09/09/1992"
    };

    // Vetor com 50 IDs fora de ordem
    int codClientes[50] = {
        35, 3, 27, 49, 12, 7, 18, 50, 42, 15,
        1, 31, 19, 23, 9, 24, 4, 36, 46, 14,
        22, 10, 32, 30, 43, 11, 16, 48, 26, 20,
        34, 21, 45, 38, 13, 17, 47, 6, 25, 5,
        2, 28, 39, 29, 44, 40, 41, 33, 8, 37
    };

    Cliente* novo_cliente;

    for (int i = 0; i < QTD_CLIENTES; i++) {
        novo_cliente = cliente(codClientes[i], nomes[i], datas[i]);
        salva(novo_cliente, out);
        free(novo_cliente);
    }
}

void le_clientes(FILE* in) {
    printf("\n\nLendo funcionários do arquivo...\n\n");
    rewind(in);
    Cliente* f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

#endif