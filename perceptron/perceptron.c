#include "perceptron.h"

void inicializa_neuronio (neoronio_t *percptron, int n_entradas) {
    int i;
    percptron->n_entradas = n_entradas;
    percptron->x = (float*) malloc (sizeof(float)*n_entradas);
    return;
}

void inicializa_peso (neoronio_t *percptron) {
    int i;
    srand(time(NULL));
    for (i = 0; i < percptron->n_entradas; i++) {
        percptron->x[i] = (rand() % 101);
        percptron->x[i] = percptron->x[i]/100;
    }
    return;
}

void inicializa_amostra (amostra *a_treimento, int entradas, int amostras) {
    int i;
    a_treimento->qtd_amostras = amostras;
    a_treimento->saidas = (int*) malloc (sizeof(int)*entradas);
    a_treimento->entradas = (int**) malloc (sizeof(int)*amostras);
    for (i = 0; i < amostras; i++) {
        a_treimento->entradas[i] = (int*) malloc (sizeof(int)*entradas);
    }
    return;
}

int funcao_ativacao (int x1, int x2, float w1, float w2) {
    float net = x1 * w1 + x2*w2;
    int y = 1;
    if (net < 1) {
        y = 0;
    }
    return (y);
}

void treinamento(amostra *a, neoronio_t *neoronio, float passo) {
    int i, y;
    int nr_acertos = 0;
    float erro1 = 0.0;
    float erro2 = 0.0;
    int nr_treinamentos = 0;
    while (1){
        nr_treinamentos++;
        nr_acertos=0;
        erro1=0.0;
        erro2=0.0; 
        for (i = 0; i < neoronio->n_entradas; i++) { //treinamento
            y = funcao_ativacao(a->entradas[0][i], a->entradas[1][i], neoronio->x[0], neoronio->x[1]);
            if (y == a->saidas[i]) { //comparando y com o saida desejada
                nr_acertos++;
            }
            erro1 += (a->saidas[i] - y) * a->entradas[0][i];
            erro2 += (a->saidas[i] - y) * a->entradas[1][i];
        }//fim for
        printf("Treino: %d, acertos: %d\n", nr_treinamentos, nr_acertos);
        if (nr_acertos == neoronio->n_entradas) { //convergiu
            return;
        } else { //atualizando os pesos
            neoronio->x[0] = neoronio->x[0] + passo*erro1;
            neoronio->x[1] = neoronio->x[1] + passo*erro2;
        }
    }//fim while
    return;
}