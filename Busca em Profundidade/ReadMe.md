# Busca em Profundidade

## Problema

Seja uma empresa a área com as seguintes rotas (em kilômetros):

* São Paulo a Brasília 		    1000
* Brasília a Palmas     		  1000
* São Paulo a Belo Horizonte	800
* São Paulo a Palmas		      1900
* Belo Horizonte a Fortaleza	1500
* Belo Horizonte a Manaus	    1800
* Belo Horizonte a Brasília		500
* Palmas a Salvador		        1000
* Palmas a São Luiz		        1500
* São Luiz a Manaus		        1500
* Palmas a Manaus		          1000

Desenvolver um programa que defina as rotas e as distâncias utilizando os seguintes métodos de busca:

- Profundidade
- superficie
- Subida de encosta

## Implementação
### Entrada de dados
Cada entrada no banco de dados deve conter as cidades de origem e de destino, a distância entre elas e um indicador para ajudar no retorno, conforme a seguinte estrutura:
```C
#define MAX 100
/* Estrutura do banco de dados sobre os voos */
struct FL {
  char from[20]; /* de */
  char to[20];   /* para */
  int distance;
  char skip; /* usado no retorno */
};
struct FL flight[MAX]; /* matriz de estruturas do banco de dados */
int f_pos = 0; /* numero de entradas do BD dos voos */
int find_pos = 0; /* indice de pesquisa no BD dos voos */
```
As entradas são colocadas no banco de dados, com a funçéao assert_flight(), e setup() inicializa a informação. A variável f_pos contém o índice do último item no banco de dados
No “banco de dados” ficam armazenados os fatos, o programa a ser desenvolvido usará estes fatos para chegar a uma solução. Assim podemos nos referir ao banco de dados como um banco de conhecimento.
### Rotinas de Suporte
Precisamos de uma rotina que determine se há um vôo entre as duas cidades (origem e destino). Essa função é chamada match() e devolve zero se não existe o vôo ou devolve a distância entre as duas cidades se há um vôo,
Outra rotina necessária é find() que, dada uma cidade, pesquisa no banco de dados qualquer conexão. Se uma conexão é encontrada, o nome da cidade destino e sua distância são devolvidos; caso contrário, zero é devolvido
### Retorno
O retorno é um ingrediente crucial em muitas técnicas de IA, sendo efetuado pelo uso de rotinas recursivas e de uma pilha de retorno. Quase todas as situações de retorno têm operação tipo pilha - isto é, elas são primeira a entrar e última a sair. Conforme umpercurso é explorado, nó são colocados na pilha à medida que são encontrados. A cada ponto sem saída, o último nó é retirado da pilha e um novo percurso, a partir desse ponto, é tentado. Esse processo continua até que a meta seja alcançada ou todos os percursos tenham se exaurido.
As funções push() e pop(), que gerenciam a pilha de retorno, mostradas a seguir, usam as variáveis globais tos e bt_stack para guardar o apontador ao topo da pilha e a matriz que contém a pilha, repectivamente.
Isflight() opera da seguinte forma. Em primeiro lugar, o banco de dados é verificado por match() para ver se existe um vôo entre from e to. Se existir a meta já foi encontrada - a conexão é colocada na pilha e a função retorna. Caso contrário, find() verifica se há alguma conexão entre from e algum outro lugar. Se houver, essa conexão é colocada na pilha e isflight() é chamada recursivamnte. Esse processo continua até que a meta seja encontrada. O campo skip é necessário no retorno para evitar que as mesmas conexões sejam tentadas repetidamente.
Isflight() não devolve a solução ela a gera. Ao sair isflight() deixa na pilha de retorno a rota entre as cidades origem e destino que é a solução.
### Resultado
A função route() serve para escrever o percurso a seguir e a distância total percorrida


