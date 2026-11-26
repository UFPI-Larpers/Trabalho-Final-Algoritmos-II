#include <stdio.h>

typedef struct {
    int idAmigo, tempoRespostaTotal, flagEnviado, tempoRecebimento; // flagEnviado serve pra avisar se Sara já respondeu ou não cada amigos
} Amigo;

typedef struct {
    char tipoRegistro;
    int tempo, amigo;
} registro;

void limparBuffer () {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscarIndiceAmigo (Amigo *p, int amigo) { // Função de busca no "banco de dados", procura se o amigo já existe.
    for (int i = 0; i < 20; i++) {
        if ((p + i)->idAmigo == amigo) {
            return i; // Se existir retorna o índice dele do vetor amigos que está na main.
        }
    }
    return -1; // Se não existir retorna -1 (Sara ainda não recebeu nenhuma mensagem desse amigo).
}

void erro (registro *vetorRegistros, int indice, Amigo *ponteiro) {
    int idx;

    if ((vetorRegistros + indice)->tipoRegistro == 'R') {
        do {
            printf ("\n\nNão tem como esse registro ser do tipo \"R\" do mesmmo amigo, pois Sara só pode receber uma única mensagem por vez e por pessoa, até que ela responda essa mensagem.\nCorrija e tente novamente:");
            printf ("\nQual o número referente ao amigo da Sara? ");
            scanf ("%d", &(vetorRegistros + indice)->amigo);
            printf ("\n\nQual o tipo do %d° registro?\n\nR - Recebido por Sara,\nE - Enviado por Sara\n. ", indice + 1);
            limparBuffer ();
            scanf (" %c", &(vetorRegistros + indice)->tipoRegistro);

            idx = buscarIndiceAmigo(ponteiro, (vetorRegistros + indice)->amigo);
        } while (((vetorRegistros + indice)->tipoRegistro == 'R' && idx != -1 && (ponteiro + idx)->flagEnviado == 0) ||
                 ((vetorRegistros + indice)->tipoRegistro == 'E' && (idx == -1 || (ponteiro + idx)->flagEnviado == 1)));
    }
    else if ((vetorRegistros + indice)->tipoRegistro == 'E') {
        do {
            printf ("\n\nEsse registro não pode ser do tipo \"E\". Sara só pode responder mensagens se já recebeu uma desse amigo (%d) e ainda não respondeu.\nCorrija e tente novamente:", (vetorRegistros + indice)->amigo);
            printf ("\nQual o número referente ao amigo da Sara? ");
            scanf ("%d", &(vetorRegistros + indice)->amigo);
            printf ("\n\nQual o tipo do %d° registro?\n\nR - Recebido por Sara,\nE - Enviado por Sara\n. ", indice + 1);
            limparBuffer ();
            scanf (" %c", &(vetorRegistros + indice)->tipoRegistro);

            idx = buscarIndiceAmigo(ponteiro, (vetorRegistros + indice)->amigo);
        } while (((vetorRegistros + indice)->tipoRegistro == 'E' && (idx == -1 || (ponteiro + idx)->flagEnviado == 1)) ||
                 ((vetorRegistros + indice)->tipoRegistro == 'R' && idx != -1 && (ponteiro + idx)->flagEnviado == 0));
    }
}

int attTempoRespostaTotal (Amigo *p, int amigo, int tempoResposta) {
    int idx = buscarIndiceAmigo(p, amigo);
    if (idx != -1) { // Testa se a pessoa já existe e ainda n foi respondida. 
        (p + idx)->tempoRespostaTotal += tempoResposta; // Faz a soma dos "Tempo Resposta Total"
        return 1;
    }
    return 0;
}

void lerProcessarRegistros (registro *vetorRegistros, int tam, Amigo *ponteiro) {
    int i, somatorioTempo = 0, j = 0;
    char flagTempo;

    for (i = 0; i < tam; i++) {
        if (i > 0) {
            printf ("\n\nHá registro de tempo entre esse e o evento anterior?\n\ns - Sim.\nn - Não.\n");
            scanf (" %c", &flagTempo);
            if (flagTempo == 's') {
                printf ("\nQual o tempo em segundos entre os dois eventos anteriores?");
                scanf ("%d", &(vetorRegistros + i)->tempo);
                somatorioTempo += (vetorRegistros + i)->tempo;
                i++;
            }
            else {
                somatorioTempo++;
            }
        }

        if (i < tam) {
            printf ("\nQual o número referente ao amigo de Sara? ");
            scanf ("%d", &(vetorRegistros + i)->amigo);
            printf ("\nQual o tipo do %d° registro?\n\nR - Recebido por Sara,\nE - Enviado por Sara.\n ", i + 1);
            limparBuffer ();
            scanf (" %c", &(vetorRegistros + i)->tipoRegistro);

            int idAtual = (vetorRegistros + i)->amigo;
            int idx = buscarIndiceAmigo(ponteiro, idAtual); // Busca se essa pessoa já existe na lista, se existir retorna o indice, se não existir ainda ele preenche as informação da lista final.

            if ((vetorRegistros + i)->tipoRegistro == 'R') {
                if (idx != -1 && (ponteiro + idx)->flagEnviado == 0) { // Se já existe e Sara ainda não envinou (não respondeu o amigo) - Mostra erro pq significa que Sara recebeu duas mensagens consecutivas da mensma pessoa, o que não cabe nas restrições.
                    erro (vetorRegistros, i, ponteiro);
                    idAtual = (vetorRegistros + i)->amigo;
                    idx = buscarIndiceAmigo(ponteiro, idAtual);
                }
                if (idx == -1) { // Se o amigo ainda não existia - SAra ainda não tinha recebido mensagem desse amigo
                    (ponteiro + j)->idAmigo = idAtual; // Armazena o amigo no BD.
                    (ponteiro + j)->tempoRespostaTotal = 0; // Inicia o tempo resposta total do amigo como 0.
                    (ponteiro + j)->tempoRecebimento = somatorioTempo; // Armazena o ponto de recebimento
                    (ponteiro + j)->flagEnviado = 0; // falg q garante que o amigo no id atual ainda não foi respondido.
                    j++;
                } else if (idx != -1 && (ponteiro + idx)->flagEnviado == 1) { // Se já existia atualiza para o próximo tempo resposta desse amigo e flagEnviado = 1 (Sara já) respondeu.
                    (ponteiro + idx)->tempoRecebimento = somatorioTempo;
                    (ponteiro + idx)->flagEnviado = 0;
                }
            }

            else if ((vetorRegistros + i)->tipoRegistro == 'E') {
                if (idx == -1 || (ponteiro + idx)->flagEnviado == 1) { // Teste se o amigo ainda não existe ou se o último registro dele for do tipo "E"
                    erro (vetorRegistros, i, ponteiro);
                    idAtual = (vetorRegistros + i)->amigo;
                    idx = buscarIndiceAmigo(ponteiro, idAtual);
                }
                int tempoResp = (idx != -1 && (ponteiro + idx)->flagEnviado == 0) ? (somatorioTempo - (ponteiro + idx)->tempoRecebimento) : 0; // Se o amigo já existe e sua flagEnviado vale zero (ainda pode ser respodido) então tem mensagem pra ser respondida, então é feito o calculo e armazenado a diferença entre os pontos no tempo, obetendo a "distância" entre eles.
                int encontrou = attTempoRespostaTotal (ponteiro, idAtual, tempoResp); // busca o amigo, atualiza o tempo resposta total e atualiza a flagEnviado.
                if (encontrou && (ponteiro + idx)->flagEnviado == 0) { // atualiza a flag para enviado = 1.
                    (ponteiro + idx)->flagEnviado = 1;
                }
            }
        }

        printf ("\n+-----------------------------------------------------------------------------------------------------------------------+");
    }
}


void ordenarAmigos (Amigo *p, int qtd) { // Ordena os amigos em ordem crescente.
    Amigo aux;
    for (int i = 0; i < qtd; i++) { // Percoore os amigos de Sara.
        for (int j = i + 1; j < qtd; j++) {
            if ((p + i)->idAmigo > (p + j)->idAmigo) {
                aux = *(p + j);
                *(p + j) = *(p + i);
                *(p + i) = aux;
            }
        }
    }
}

void mostrarTempoRespostaTotal (Amigo *p) {
    int qtd = 0, i = 0;
    while ((p + i)->idAmigo != 0 && i < 20) { // Acha quantos amigos existem no "banco de dados" (vetor amigos)
        qtd++;
        i++;
    }
    ordenarAmigos(p, qtd);

    printf ("\n");
    for (i = 0; i < qtd; i++) {
        if ((p + i)->flagEnviado == 1) {
            printf ("\n%d %d", (p + i)->idAmigo, (p + i)->tempoRespostaTotal);
        }
        else if ((p + i)->flagEnviado == 0){
            printf ("\n%d -1", (p + i)->idAmigo); // Se ao final a flagEnviado desse amigo ainda valer 0, significa que n foi respondido, logo sua saída é '-1'. 
        }
    }
}

int main () {
    int qntdRegistros;
    Amigo amigos[20] = {0};

    printf ("Quantos registros quer analisar? ");
    scanf ("%d", &qntdRegistros);

    registro Registros[qntdRegistros];

    lerProcessarRegistros (Registros, qntdRegistros, amigos);
    mostrarTempoRespostaTotal (amigos);
    return 0;
}