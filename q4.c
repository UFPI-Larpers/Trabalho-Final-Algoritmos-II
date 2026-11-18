#include <stdio.h>

typedef struct No{
    int valor;
    struct No *proximo;
}No;

void inserir(No *vetor, int *qtd, int valor){
    // se qtd for 10, impede de dar overflow
    if(*qtd >= 10) return;

    // se for maior que zero, ve se o anterior ta apontando pra nulo, inseriu, aponta pro novo no
    if(*qtd > 0){
        (vetor + (*qtd) - 1)->proximo = (vetor+*qtd);
    }

    // aqui to definindo o valor do novo no, e botando ele pra apontar pra nulo
    (vetor + *qtd)->valor = valor;
    (vetor + *qtd)->proximo = NULL;
    
    // e aqui to incrementando a quantidade de nos que ja existem
    (*qtd)++;
}

// nessa aqui nao vi necessidade de usar o qtd como parametro
void mostrar(No *vetor){
    // o no atual recebe a posicao 0 do vetor
    No *atual = vetor;
    
    // e aqui vai printando e incrementando pro proximo ate que a posicao atual seja nula
    while(atual != NULL){
        printf("%d ", atual->valor);
        // isso e um tipo de "Incremento"
        atual = atual->proximo;
    }
}

int main(){
    // declaro aqui o vetor de nos
    No nozes[10];

    int qtd = 0;

    int valor;

    // e aqui leio com um for "dinamicamente"
    for(int i = 0; i < 10; i++){
        printf("Digite um valor: ");
        scanf("%d", &valor);
        inserir(nozes, &qtd, valor);
    }

    mostrar(nozes);

    return 0;
}