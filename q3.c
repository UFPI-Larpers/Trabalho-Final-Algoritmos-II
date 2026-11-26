#include <stdio.h>

#define L 4
#define C 5

void lerMatriz (int **mat, int l, int c) {
    int i, j;
    for (i = 0; i < l; i++) { 
        for (j = 0; j < c; j++) { 
            printf ("\nDigite o valor do elemento na posição [%d][%d]: ", i + 1, j + 1);
            scanf ("%d", *(mat + i) + j); 
        }
    }
}

int processarMatriz (int **mat, int l, int c) {
    int i, j, contador = 0;
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            if (*(*(mat + i) + j) < 0) {
                *(*(mat + i) + j) = 0;
                contador++;
            }
        }
    }
    return contador;
}

void imprimirMatrizProcessada (int **mat, int l, int c) {
    int i, j;
    
    for (i = 0; i < l; i++) {
        for (j = 0; j < c; j++) {
            printf ("%4d", *(*(mat + i) + j));
        }
        printf ("\n");
    }
}

int main () {
    
    int C_L0[C], C_L1[C],  C_L2[C], C_L3[C]; // Vai indicar os endereços das colunas de cada linha.
    int *mat[L] ; // Vai apontar o endereço das linhas de cada coluna
    *(mat + 0) = C_L0; 
    *(mat + 1) = C_L1; 
    *(mat + 2) = C_L2;
    *(mat + 3) = C_L3;


    lerMatriz (mat, L, C);
    int qntdSubstituidos = processarMatriz (mat, L, C);
    imprimirMatrizProcessada (mat, L, C);

    printf ("\nQuantidade de números substituídos: %d", qntdSubstituidos);
    
    return 0;

}