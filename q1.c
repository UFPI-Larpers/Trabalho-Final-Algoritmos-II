#include <stdio.h>
#include <string.h>

// inverter a string
void inverterString(char *string, char *nova){
    int i = 0, fim = strlen(string) - 1;

    while(*(string + i) != '\0'){
        // ja decrementa o fim junto com a aritmetica
        *(nova + i) = *(string + (fim--));
        
        i++; 
    }

    *(nova + i) = '\0';
}

void compararStrings(char *string, char *nova){
    int i = 0;
    int pal = 1;

    // vetor que armazena a contagem de indices iguais
    int positions[strlen(string)];

    for(int j = 0; j < strlen(string); j++){
        *(positions + j) = 0;
    }

    while(*(string + i) != '\0'){
        if(*(string + i) != *(nova + i)){
            pal = 0;
        }else{
            // incrementa a contagem do vetor no indice i
            *(positions + i) += 1;
        }
        i++;
    }

    // verificacao, avisa se for palindromo, mostra quantas posições iguais se não for.
    if(pal == 1){
        printf("É um palindromo!\n");
    }else{
        for(int j = 0; j < strlen(string); j++){
            if(*(positions + j) > 0){
                printf("Numero de caracteres iguais na posicao [%d]: %d\nCaractere: '%c'\n", j, *(positions + j), *(string + j));
            }
        }
        printf("Não é palindromo!\n");
    }

}

void contarOcorrencias(char *string){
    int i = 0;
    
    int ocorrencias['z'];

    // zera todas as posições de 'A' a 'z'
    for(char j = 'A'; j <= 'z'; j++){
        *(ocorrencias + j) = 0;
    }

    // percorre toda a string e itera com caracteres, contando cada ocorrencia
    while(*(string + i) != '\0'){
        // percorre com um iterador de char
        for(char j = 'A'; j <= 'z'; j++){
            // se o conteudo de string[i] for IGUAL ao j (caractere), incrementa ocorrencias no indice j (caractere).
            if(*(string + i) == j){
                *(ocorrencias + j) += 1;
                break;
            }
        }
        i++;
    }

    // percorre com iterador de char para printar nas devidas posições
    for(char j = 'A'; j <= 'z'; j++){
        // printa somente se for maior que zero
        if(*(ocorrencias + j) > 0){
            printf("Numero de vezes que o '%c' aparece na string: %d\n", j, *(ocorrencias + j));
        }
    }
}

void mostrarResultados(char *string, char *nova){
    inverterString(string, nova);
    
    printf("String: %s\nNova: %s\n", string, nova);
    
    compararStrings(string, nova);

    contarOcorrencias(string);
}

int main(){
    char string[100];
    char nova[100];
    printf("Digite uma string qualquer: ");
    scanf("%99[^\n]", string);

    mostrarResultados(string, nova);

    return 0;
}