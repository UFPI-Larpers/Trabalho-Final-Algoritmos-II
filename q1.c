#include <stdio.h>
#include <string.h>

void inverterString(char *string, char *nova){
    int i = 0, fim = strlen(string) - 1;

    while(*(string + i) != '\0'){
        *(nova + i) = *(string + (fim--));
        
        i++; 
    }

    *(nova + i) = '\0';
}

void compararStrings(char *string, char *nova){
    int i = 0;
    int pal = 1;

    int positions[strlen(string)];

    for(int j = 0; j < strlen(string); j++){
        *(positions + j) = 0;
    }

    while(*(string + i) != '\0'){
        if(*(string + i) != *(nova + i)){
            pal = 0;
        }else{
            *(positions + i) += 1;
        }
        i++;
    }

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

    for(char j = 'A'; j < 'z'; j++){
        *(ocorrencias + j) = 0;
    }

    while(*(string + i) != '\0'){
        for(char j = 'A'; j < 'z'; j++){
            if(*(string + i) == j){
                *(ocorrencias + j) += 1;
            }
        }
        i++;
    }

    for(char j = 'A'; j < 'z'; j++){
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