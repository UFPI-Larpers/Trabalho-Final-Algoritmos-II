#include <stdio.h>

typedef struct {
    int idAmigo, tempoRespostaTotal, flagEnviado, tempoRecebimento;
} Amigo;

typedef struct {
    char tipoRegistro;
    int tempo, amigo;
} registro;

void limparBuffer () {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscarIndiceAmigo (Amigo *p, int amigo) {
    for (int i = 0; i < 20; i++) {
        if ((p + i)->idAmigo == amigo) {
            return i;
        }
    }
    return -1;
}

int teste (Amigo *p, int amigo, int tempoResposta) {
    int idx = buscarIndiceAmigo(p, amigo);
    if (idx != -1 && (p + idx)->flagEnviado == 0) { // Testa se a pessoa já existir e ainda n foi respondida. 
        (p + idx)->tempoRespostaTotal += tempoResposta; // Faz a soma dos "Tempo Resposta Total"
        (p + idx)->flagEnviado = 1; // Flag que garante que a resposta foi respodida 
        return 1;
    }
    return 0;
}

void lerRegistros (registro *vetorRegistros, int tam, Amigo *ponteiro) {
    int i, somatorioTempo = 0, j = 0;
    char flagTempo;

    for (i = 0; i < tam; i++) {
        if (i > 0) {
            printf ("\nHá registro de tempo entre esse e o evento anterior?\n\ns - Sim.\nn - Não.\n");
            scanf (" %c", &flagTempo);
            if (flagTempo == 's') {
                printf ("\nQual o tempo em segundos entre os dois eventos anteriores?");
                scanf ("%d", &(vetorRegistros + i)->tempo);
                somatorioTempo += (vetorRegistros + i)->tempo;
            }
            else {
                somatorioTempo++;
            }
        }

        printf ("\n\nQual o tipo do %d° registro?\n\nR - Recebido por Sara,\nE - Enviado por Sara\n. ", i + 1);
        limparBuffer ();
        scanf (" %c", &(vetorRegistros + i)->tipoRegistro);
        printf ("\nQual o número referente ao amigo da Sara? ");
        scanf ("%d", &(vetorRegistros + i)->amigo);

        int idAtual = (vetorRegistros + i)->amigo;
        int idx = buscarIndiceAmigo(ponteiro, idAtual); // Busca se essa pessoa já existe na lista, se existir retorna o indice, se não existir ainda ele preenche as informação da lista final.

        if ((vetorRegistros + i)->tipoRegistro == 'R') {
            if (idx == -1) {
                (ponteiro + j)->idAmigo = idAtual;
                (ponteiro + j)->tempoRespostaTotal = 0;
                (ponteiro + j)->tempoRecebimento = somatorioTempo; // Armazena o ponto de recebimento
                (ponteiro + j)->flagEnviado = 0; // falg q garante que o amigo no id atual ainda não foi respondido.
                j++;
            } else {
                do {
                    printf ("\n\nNão tem como esse registro ser do tipo \"R\" pois Sara só pode receber uma única mensagem por vez e por pessoa");
                }
            }
        }
        else if ((vetorRegistros + i)->tipoRegistro == 'E') {
            int tempoResp = (idx != -1) ? (somatorioTempo - (ponteiro + idx)->tempoRecebimento) : 0; // Se já existe então tem mensagem pra ser respondida, então é feito o calculo e armazenado a diferença entre os pontos no tempo, obetendo a "distância" entre eles.
            int encontrou = teste (ponteiro, idAtual, tempoResp); // busca o amigo, atualiza o tempo resposta total e atualiza a flagEnviado.
            if (!encontrou) { // Se não encontrou o amigo (encontrou = 0) - Sara enviou uma mensagem pra um amigo que aida não respondeu
                (ponteiro + j)->idAmigo = idAtual;
                (ponteiro + j)->tempoRespostaTotal = tempoResp; // Então o temp
                (ponteiro + j)->flagEnviado = 1;
                j++;
            }
        }

        printf ("\n+-----------------------------------------------------------------------------------------------------------------------+");
    }
}

void ordenarAmigos (Amigo *p, int qtd) {
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = 0; j < qtd - 1 - i; j++) {
            if ((p + j)->idAmigo > (p + j + 1)->idAmigo) {
                Amigo aux = *(p + j);
                *(p + j) = *(p + j + 1);
                *(p + j + 1) = aux;
            }
        }
    }
}

void mostrarTempoRespostaTotal (Amigo *p) {
    int qtd = 0;
    while ((p + qtd)->idAmigo != 0 && qtd < 20) {
        qtd++;
    }
    ordenarAmigos(p, qtd);

    printf ("\n");
    for (int i = 0; i < qtd; i++) {
        if ((p + i)->flagEnviado == 1) {
            printf ("\n%d %d", (p + i)->idAmigo, (p + i)->tempoRespostaTotal);
        }
        else {
            printf ("\n%d -1", (p + i)->idAmigo);
        }
    }
}

int main () {
    int qntdRegistros;
    Amigo amigos[20] = {0};

    printf ("Quantos registros quer analisar? ");
    scanf ("%d", &qntdRegistros);

    registro Registros[qntdRegistros];

    lerRegistros (Registros, qntdRegistros, amigos);
    mostrarTempoRespostaTotal (amigos);
    return 0;
}