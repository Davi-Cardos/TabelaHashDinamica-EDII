#include "Cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


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

    int elementoASerDuplicado = tabela->proximoCompartimento;

    int posicao = funcaoHash(cliente->codCliente, tabela->tamanhoUnical, tabela->duplicacoes);

    if(posicao < elementoASerDuplicado) {
        posicao = funcaoHash(cliente->codCliente, tabela->tamanhoUnical, tabela->duplicacoes + 1);
    }
   

    ENDERECO * novoCliente = (ENDERECO *) malloc(sizeof(ENDERECO));
    novoCliente->cliente = cliente;
    novoCliente->prox = NULL;

    if(fatorCarga(tabela->numeroElementosNaTabela, tabela->tamanhoAtual, tabela->fatorCarga) == 1) {

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

void imprimirTabela(TABELAHASH *tabela) {
    printf("\nEstado atual da Tabela Hash:\n");
    for (int i = 0; i < tabela->tamanhoAtual; i++) {
        printf("Posição %d: ", i);
        ENDERECO *atual = tabela->tabela[i];
        while (atual != NULL) {
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

int main() {
    int tamanhoInicial = 7;
    int fatorCarga = 1;
    TABELAHASH *tabela = inicializarTABELAHASH(tamanhoInicial, fatorCarga);

    // Criação de clientes
    CLIENTE *cliente1 = Cliente(49, "Joao");
    CLIENTE *cliente2 = Cliente(51, "Carla");
    CLIENTE *cliente3 = Cliente(3, "Jose");
    CLIENTE *cliente4 = Cliente(59, "Maria");
    CLIENTE *cliente5 = Cliente(87, "Bia");
    CLIENTE *cliente6 = Cliente(103, "Ana");
    CLIENTE *cliente7 = Cliente(7, "Carlos");
    CLIENTE *cliente8 = Cliente(8, "Joao2");
    CLIENTE *cliente9 = Cliente(14, "Carol");
    CLIENTE *cliente10 = Cliente(15, "Pedro");
    CLIENTE *cliente11 = Cliente(20, "Lucas");
    CLIENTE *cliente12 = Cliente(31, "Fernanda");
    CLIENTE *cliente13 = Cliente(42, "Leonardo");
    CLIENTE *cliente14 = Cliente(53, "Paula");
    CLIENTE *cliente15 = Cliente(64, "Gabriel");
    CLIENTE *cliente16 = Cliente(75, "Julia");
    CLIENTE *cliente17 = Cliente(86, "Henrique");
    CLIENTE *cliente18 = Cliente(97, "Rafaela");
    CLIENTE *cliente19 = Cliente(108, "Marcelo");
    CLIENTE *cliente20 = Cliente(119, "Bianca");
    CLIENTE *cliente21 = Cliente(25, "Marta");
    CLIENTE *cliente22 = Cliente(37, "Eduardo");
    CLIENTE *cliente23 = Cliente(48, "Renata");
    CLIENTE *cliente24 = Cliente(59, "Roberto");
    CLIENTE *cliente25 = Cliente(63, "Aline");
    CLIENTE *cliente26 = Cliente(72, "Victor");
    CLIENTE *cliente27 = Cliente(83, "Sofia");
    CLIENTE *cliente28 = Cliente(91, "Thiago");
    CLIENTE *cliente29 = Cliente(100, "Mariana");
  
    // Inserção de clientes e impressão da tabela após cada inserção
    inserirElemento(tabela, cliente1);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente2);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente3);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente4);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente5);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente6);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente7);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente8);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente9);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente10);
    imprimirTabela(tabela);
     printf("p = %d\n", tabela->proximoCompartimento);

     inserirElemento(tabela, cliente11);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente12);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente13);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente14);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente15);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente16);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente17);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente18);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente19);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente20);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente21);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente22);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente23);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente24);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente25);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente26);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente27);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente28);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);

    inserirElemento(tabela, cliente29);
    imprimirTabela(tabela);
    printf("p = %d\n", tabela->proximoCompartimento);



    free(cliente1);
    free(cliente2);
    free(cliente3);
    free(cliente4);
    free(cliente5);
    free(cliente6);
    free(cliente7);
    free(cliente8);
    free(cliente9);
    free(cliente10);
    free(cliente11);
    free(cliente12);
    free(cliente13);
    free(cliente14);
    free(cliente15);
    free(cliente16);
    free(cliente17);
    free(cliente18);
    free(cliente19);
    free(cliente20);
    free(cliente21);
    free(cliente22);
    free(cliente23);
    free(cliente24);
    free(cliente25);
    free(cliente26);
    free(cliente27);
    free(cliente28);
    free(cliente29);
   
    liberarTabela(tabela);

    return 0;
}
