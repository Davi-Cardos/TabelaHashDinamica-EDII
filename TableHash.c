#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    CLIENTE *cliente;
    struct ENDERECO *prox;
} ENDERECO;

typedef struct {
ENDERECO **tabela; 
int tamanhoAtual; 
int fatorCarga; 
int duplicacoes; 
int proximoCompartimento; 
} TABELAHASH;

TABELAHASH* inicializarTABELAHASH(int tamanhoInicial, int fatorCarga) { 

TABELAHASH *tabela = (TABELAHASH*)malloc(sizeof(TABELAHASH)); 
tabela->tabela = (ENDERECO**)calloc(tamanhoInicial, sizeof(ENDERECO*)); 
tabela->tamanhoAtual = tamanhoInicial; 
tabela->fatorCarga = fatorCarga; 
tabela->duplicacoes = 0; 
tabela->proximoCompartimento = 0; 
return tabela;
}
