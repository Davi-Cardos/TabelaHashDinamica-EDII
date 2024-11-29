#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "addclientes.h"


typedef struct {
    CLIENTE *cliente;
    struct ENDERECO *prox;
} ENDERECO;

typedef struct {
ENDERECO **tabela; 
int tamanhoUnical;
int tamanhoAnterior;
int tamanhoAtual; 
int fatorCarga; 
int duplicacoes; 
int proximoCompartimento; 
int numeroElementosNaTabela;
} TABELAHASH;

TABELAHASH* inicializarTABELAHASH(int tamanhoInicial, int fatorCarga) { 

TABELAHASH *tabela = (TABELAHASH*)malloc(sizeof(TABELAHASH)); 
tabela->tabela = (ENDERECO**)calloc(tamanhoInicial, sizeof(ENDERECO*)); 
tabela->tamanhoUnical = tamanhoInicial;
tabela->tamanhoAnterior = tamanhoInicial;
tabela->tamanhoAtual = tamanhoInicial; 
tabela->fatorCarga = fatorCarga; 
tabela->duplicacoes = 0; 
tabela->proximoCompartimento = 0; 
tabela->numeroElementosNaTabela = 0;
return tabela;
}

void inserirElemento(TABELAHASH * tabela, CLIENTE * cliente) {

    int qtdElementos = tabela->numeroElementosNaTabela + 1;


    int elementoASerDuplicado = tabela->proximoCompartimento;

    int posicao = funcaoHash(cliente->codCliente, tabela->tamanhoUnical, tabela->duplicacoes);

    if(posicao < elementoASerDuplicado) {
        posicao = funcaoHash(cliente->codCliente, tabela->tamanhoUnical, tabela->duplicacoes + 1);
    }
   

    ENDERECO * novoCliente = (ENDERECO *) malloc(sizeof(ENDERECO));
    novoCliente->cliente = cliente;
    novoCliente->prox = NULL;

    // printf("Fator de carga: %d\n", fatorCarga(tabela->numeroElementosNaTabela, tabela->tamanhoAtual, tabela->fatorCarga));
    // printf("numeroElementosNaTabela: %d\n", tabela->numeroElementosNaTabela);
    // printf("Tamanho Atua: %d\n", tabela->tamanhoAtual);
    if(fatorCarga(qtdElementos, tabela->tamanhoAtual, tabela->fatorCarga) == 1) {

    if(tabela->tabela[posicao] == NULL) {
        tabela->tabela[posicao] = novoCliente;
    }

    //Se já possuir um cliente dentro da posição da minha tabela
    else {
        novoCliente->prox = tabela->tabela[posicao]; 
        tabela->tabela[posicao] = novoCliente; //Estou inserindo o novo cliente no inicio lista encadeada
    }

    }

    else {
    expandir(tabela);
    inserirElemento(tabela, cliente);
    return;
        

    }

    tabela->numeroElementosNaTabela++;

}

void expandir(TABELAHASH *tabela) {

    int novoTamanho = tabela->tamanhoAtual + 1;

    int qtdExpansoes = verificaDuplicacao(tabela);

    int expandirCompartimento = tabela->proximoCompartimento;

    printf("Elemento a ser expandido: %d\n", expandirCompartimento);

    int proxCompartimento = tabela->proximoCompartimento + 1;

    ENDERECO * atual = tabela->tabela[expandirCompartimento]; //Pego cada elemento que tenho na posicao. Exemplo: Tenho que expandir a posição 0, e dentro da posição 0 tenho os clientes de cod 4 e cod 8. Pego a primeria posição e vou recalculando para cada um a função hash

    ENDERECO **novaTabela = (ENDERECO **) calloc(novoTamanho, sizeof(ENDERECO *)); //Crio a nova tabela

    //Vou passar tudo que tava naquela posicao da minha tabela para o novo calculo da funcaoHash
    while(atual != NULL) {

        int novaPosicao = funcaoHash(atual->cliente->codCliente, tabela->tamanhoUnical, qtdExpansoes);

        //Cio um novo cliente na minha nva tabela redimensuionada
        ENDERECO *novoCliente = (ENDERECO *) malloc(sizeof(ENDERECO));
        novoCliente->cliente = atual->cliente;
        novoCliente->prox = novaTabela[novaPosicao];
        novaTabela[novaPosicao] = novoCliente;
        atual = atual->prox;

    }

    //Passando tudo que tava na tabela anterior para essa sem calcular a função hash dos outros

      for (int i = 0; i < tabela->tamanhoAtual; i++) {
        if (i == expandirCompartimento) continue; 

        ENDERECO *atual = tabela->tabela[i];
        while (atual != NULL) {
            // Cria um novo nó na nova tabela
            ENDERECO *novoCliente = (ENDERECO *)malloc(sizeof(ENDERECO));
            novoCliente->cliente = atual->cliente;
            novoCliente->prox = novaTabela[i];  // Insere no início da lista encadeada
            novaTabela[i] = novoCliente;  // Atualiza a nova tabela

            atual = atual->prox;  // Avança para o próximo cliente
        }
    }


    free(tabela->tabela);

    tabela->tabela = novaTabela;
    tabela->tamanhoAtual = novoTamanho;
    tabela->proximoCompartimento = proxCompartimento;


}

int funcaoHash(int valor, int m, int l) {
    return valor % (m * (int)(pow(2, l))); //Asseguro que o valor da potencia sempre será um inteiro porque a funcao pow retorna double

}

int fatorCarga(int num, int m, int fatorCarga) {

    if(num / m < fatorCarga) {
        return 1;
    }

    else {
        return 0;
    }

}

int verificaDuplicacao(TABELAHASH *tabela) {

    //O que estou fazendo aqui é justamente verificando se meu p chegou ao fim da minha tabela inicial. Se chegou minha tabela agr vai ter o tamanho atual o p volta a aser 0 e a duplicação passa a ter valor 1 para todos
    int qtdExpansoes = tabela->duplicacoes;

    if(tabela->proximoCompartimento == tabela->tamanhoAnterior) {

        tabela->tamanhoAnterior = tabela->tamanhoAtual;
        tabela->proximoCompartimento = 0;
        tabela->duplicacoes = tabela->duplicacoes + 1;

    }

    //Se meu p não chegou no final, então eu apenas pego a quantidade de duplicações e aumento 1 na variável. se ele chegou até o final atualizo a minha qtd de duplicações atualizada e aumento mais 1 pois calculo minha nova função hash
    //Exemplo x % 7 e x % 14 nas expansões, quando p expandir o 6 (0-6) chegarei no comprimento da minha tabela então p voltará a ser 0 e minha nova função hash será x % 14 e x% 28 na expansão  
    return tabela->duplicacoes + 1;


}

void imprimirTabela(TABELAHASH *tabela, FILE *arquivo) {
    fseek(arquivo, 0, SEEK_SET); // Posiciona no início do arquivo
    printf("\nEstado atual da Tabela Hash (lido do arquivo):\n");

    // Ler os dados diretamente do arquivo para reconstruir a tabela hash
    for (int i = 0; i < tabela->tamanhoAtual; i++) {
        printf("Posição %d: ", i);

        // Para cada posição, simula a leitura de uma lista encadeada
        ENDERECO *atual = tabela->tabela[i];
        while (atual != NULL) {
            // Exibir cliente
            printf("-> Cliente %d (%s) ", atual->cliente->codCliente, atual->cliente->nome);
            atual = atual->prox;
        }

        printf("-> NULL\n");
    }
    printf("\n");
}

void liberarTabela(TABELAHASH *tabela) {
    for (int i = 0; i < tabela->tamanhoAtual; i++) {
        ENDERECO *atual = tabela->tabela[i];
        while (atual != NULL) {
            ENDERECO *temp = atual;
            atual = atual->prox;
            free(temp->cliente); // Libera o cliente associado
            free(temp);          // Libera o nó ENDERECO
        }
    }
    free(tabela->tabela); // Libera o array de ponteiros da tabela hash
    free(tabela);          // Libera a estrutura TABELAHASH
}

void salvarTabelaNoArquivo(TABELAHASH *tabela, FILE *arquivo) {
    for (int i = 0; i < tabela->tamanhoAtual; i++) {
        if (tabela->tabela[i] != NULL) {
            fwrite(tabela->tabela[i], sizeof(CLIENTE), 1, arquivo);
        }
    }
}


int main() {
    int tamanhoInicial = 3;
    int fatorCarga = 1;
    TABELAHASH *tabela = inicializarTABELAHASH(tamanhoInicial, fatorCarga);

    FILE *clientes = fopen("clientes.dat", "w+b");
    FILE *arquivo_hash = fopen("hash.dat", "w+b");

    if(clientes == NULL || arquivo_hash == NULL) {
        printf("Não foi possível abrir o arquivo");
        exit(1);
    }

    insere_clientes(clientes);
    rewind(clientes);

    CLIENTE * cliente = (CLIENTE *) malloc(sizeof(CLIENTE));


    while(fread(cliente, sizeof(CLIENTE), 1, clientes) == 1) {
        CLIENTE *clienteTab = Cliente(cliente->codCliente, cliente->nome);
        inserirElemento(tabela, clienteTab);
        salvarTabelaNoArquivo(tabela, arquivo_hash);
        imprimirTabela(tabela, arquivo_hash);

    }

    free(cliente);
    fclose(clientes);
    fclose(arquivo_hash);
    liberarTabela(tabela);

    return 0;
}
