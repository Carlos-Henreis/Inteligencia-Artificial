/* 
 * File:   perceptron.h
 * Author: Particular
 *
 * Created on 28 de Setembro de 2016, 23:12
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef PERCEPTRON_H
#define	PERCEPTRON_H
struct neoronio {
    //links de conexão são descartados pois só nos ineteressa o peso
    int n_entradas;
    float *x;//pesos das entradas
};

struct amostra_treinamento {
    int qtd_amostras;
    int **entradas;
    int *saidas;

};

typedef struct neoronio neoronio_t;
typedef struct amostra_treinamento amostra;

void inicializa_neuronio (neoronio_t *percptron, int n_entradas);

void inicializa_peso (neoronio_t *percptron);

void inicializa_amostra (amostra *a_treimento, int entradas, int amostras);

int funcao_ativacao (int x1, int x2, float w1, float w2);

void treinamento(amostra *a, neoronio_t *neoronio, float passo);

#endif	/* PERCEPTRON_H */

