#include <stdio.h>
#include <string.h>

#define MAX 100

/* Estrutura do banco de dados sobre os voos */
struct FL {
	char from[20]; /* de */
	char to[20];   /* para */
	int distance;
	char skip; /* usado no retorno */
};

typedef struct FL FL;

FL flight[MAX]; /* matriz de estruturas do banco de dados */

/*Variaveis globais*/
int f_pos = 0; /* numero de entradas do BD dos voos */
int find_pos = 0; /* indice de pesquisa no BD dos voos */
int tos =0;
FL bt_stack[MAX];

/* Coloca os fatos no banco de dados */
void assert_flight(char *from, char *to, int dist) {
	if (f_pos < MAX) {
		strcpy(flight[f_pos].from,from);
		strcpy(flight[f_pos].to,to);
		flight[f_pos].distance = dist;
		flight[f_pos].skip = 0;
		f_pos++;
	}
	else printf("banco de dados de v“os cheio.\n");
}

void setup(void) {
	assert_flight("Sao Paulo","Brasilia",1000);
  	assert_flight("Brasilia","Palmas",1000);
  	assert_flight("Sao Paulo","Belo Horizonte",800);
	assert_flight("Sao Paulo","Palmas",1900);
	assert_flight("Belo Horizonte","Fortaleza",1500);
	assert_flight("Belo Horizonte","Manaus",1800);
	assert_flight("Belo Horizonte","Brasilia",500);
	assert_flight("Palmas","Salvador",1000);
	assert_flight("Palmas","Sao Luis",1500);
	assert_flight("Sao Luis","Manaus",1500);
	assert_flight("Palmas","Manaus",1000);
}

/* se ha o voo entre from e to, entao devolve a distancia do voo; caso */
/* contrario, devolve 0 */
int match(char *from, char *to) {  
	int t;
	for (t =f_pos-1; t>-1; t--){
		
		if(strcmp(flight[t].from,from) == 0 && strcmp(flight[t].to,to) == 0) {
				return flight[t].distance;
		}
	}
	return 0;    /* nao encontrado */
}

/* Dado from, encontre anywhere */
int find (char *from, char *anywhere) {
	find_pos = 0;
  	while (find_pos < f_pos) {
   		if (strcmp(flight[find_pos].from, from)==0 && flight[find_pos].skip == 0) {
     		strcpy(anywhere, flight[find_pos].to);
     		flight[find_pos].skip = 1;     /* torna ativo */
     		return flight[find_pos].distance;
   		}
   		find_pos++;
 	}
 	return 0;
}

/* Rotinas de pilha */
void push (char *from, char *to, int dist) { 
	if(tos < MAX ) {
  		strcpy(bt_stack[tos].from,from);
  		strcpy(bt_stack[tos].to,to);
  		bt_stack[tos].distance=dist;
  		tos++;
 	} 
 	else 
 		printf("Pilha cheia \n");
 	return;
}

void pop (char *from, char *to, int dist) { 
	if(tos > 0) {
  		tos--;
  		strcpy(from,bt_stack[tos].from);
  		strcpy(to,bt_stack[tos].to);
  		dist = bt_stack[tos].distance;
 	} 
 	else 
 		printf("Pilha vazia \n");
 	return;
}

/* Determina se ha uma rota entre from e to */
/* Determina se ha uma rota entre from e to */
void isflight(char *from, char *to) {
	int d, dist;
 	char anywhere[20];
 	d = match(from,to);
 	if (d != 0) {
  		push(from, to, d);  /* ‚ a meta */
  		return;  
  	}
	/* Tenta outra conexao */
  	dist=find(from,anywhere);

 	if(dist != 0) {
   		push (from, to, dist);
   		isflight (anywhere, to);
  	}
  	else 
  		if(tos > 0) {
   			pop(from,to,dist);
   			isflight(from,to);
  		} 
}
/* Mostra a rota e a distancia total */
void route(char *to) {
  	int dist, t;
  	dist = 0;
  	t = 0;
  	while (t < tos) {
   		printf("%s para ", bt_stack[t].from);
   		dist += bt_stack[t].distance;
   		t++;
  	}
  	printf("%s \n",to);
  	printf("distancia :%d\n",dist);
}

void imprime (void) {
	int i;
	for (i = 0; i < f_pos; i++){
		printf ("%s ", flight[i].from);
		printf ("%s ", flight[i].to);
		printf("%d\n",flight[i].distance);
	}
}

int main(void) {
	
	char from[20],/* de */
		 to[20];  /* para */ 

	setup();/*Inicializa a base de dados com a conexão*/

	do {/*Sai do loop quando as entradas são iguais*/
		/*Entrada com os dados*/
		printf("Entre com a cidade de origem\n");
		scanf (" %[^\n]s", from);
		printf("Entre com a cidade de destino\n");
		scanf (" %[^\n]s", to);
		/*Chamadas das funcções de verificações*/
		isflight(from,to);
		route(to);
		printf("%s, %s\n", from, to);
	} while (strcmp(from, to) == 0);
	return 0;
}
