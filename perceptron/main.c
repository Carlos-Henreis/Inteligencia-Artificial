#include <stdio.h>
#include "perceptron.h"

#define NRCASOS 4

int main(void) {
    neoronio_t *neoronio;
    amostra *a;
    int vet1[NRCASOS] = {0, 0, 1, 1};;
    int vet2[NRCASOS] = {0, 1, 0, 1};
    int vet3[NRCASOS] = {0, 1, 1, 1};
    int vet4[NRCASOS] = {0, 0, 0, 1};
    float passo = 0.05;//Constante de aprendizado
    a = (amostra*) malloc (sizeof(amostra));
    neoronio = (neoronio_t*) malloc (sizeof(neoronio_t));
    inicializa_neuronio(neoronio, NRCASOS);
    inicializa_amostra(a, NRCASOS, 2);
    inicializa_peso(neoronio);
    //treinando para or
    a->entradas[0] = vet1;
    a->entradas[1] = vet2;
    a->saidas = vet3;

    treinamento(a, neoronio, passo);
    //teste com a rede já treinada
    printf("Pesos Finais: w1: %f, w2: %f, \n", neoronio->x[0], neoronio->x[1]);
    printf ("%d %d = %d\n", 0, 0, funcao_ativacao (0, 0, neoronio->x[0], neoronio->x[1]));
    printf ("%d %d = %d\n", 0, 1, funcao_ativacao (0, 1, neoronio->x[0], neoronio->x[1]));
    printf ("%d %d = %d\n", 1, 0, funcao_ativacao (1, 0, neoronio->x[0], neoronio->x[1]));
    printf ("%d %d = %d\n", 1, 1, funcao_ativacao (1, 1, neoronio->x[0], neoronio->x[1]));
 
    //treinando para and
    a->saidas = vet4;
    inicializa_peso(neoronio);
    treinamento(a, neoronio, passo);
    //teste com a rede já treinada
    printf("Pesos Finais: w1: %f, w2: %f, \n", neoronio->x[0], neoronio->x[1]);
    printf ("%d %d = %d\n", 0, 0, funcao_ativacao (0, 0, neoronio->x[0], neoronio->x[1]));
    printf ("%d %d = %d\n", 0, 1, funcao_ativacao (0, 1, neoronio->x[0], neoronio->x[1]));
    printf ("%d %d = %d\n", 1, 0, funcao_ativacao (1, 0, neoronio->x[0], neoronio->x[1]));
    printf ("%d %d = %d\n", 1, 1, funcao_ativacao (1, 1, neoronio->x[0], neoronio->x[1]));
} 