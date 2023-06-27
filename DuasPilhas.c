#include <stdio.h>

#define TAM 10

void push(int *topo, int valor, int P[]);
void imprimir_pilha(int P[], int topo);
void push_ordenado_P3(int P1[], int P2[], int P3[], int *topo1, int *topo2, int *topo3);
int pop(int *topo, int P[]);



int main(){
	int P1[TAM] = {0}, P2[TAM] = {0}, P3[TAM] = {0};
	int topo1 = 0, topo2 = 0, topo3 = 0;

	push(&topo1, 8, P1);
	push(&topo1, 4, P1);
	push(&topo1, 1, P1);

	push(&topo2, 9, P2);
	push(&topo2, 7, P2);
	push(&topo2, 6, P2);
	push(&topo2, 2, P2);

	printf("------P1-------\n");
	imprimir_pilha(P1, topo1);
	printf("------P2-------\n");
	imprimir_pilha(P2, topo2);

	printf("topo 1: %i\n", topo1);
	printf("topo 2: %i\n", topo2);
	printf("topo 3: %i\n", topo3);

	push_ordenado_P3(P1, P2, P3, &topo1, &topo2, &topo3);

	printf("------P1-------\n");
	imprimir_pilha(P1, topo1);
	printf("------P2-------\n");
	imprimir_pilha(P2, topo2);
	printf("------P3-------\n");
	imprimir_pilha(P3, topo3);

	printf("topo 1: %i\n", topo1);
	printf("topo 2: %i\n", topo2);
	printf("topo 3: %i\n", topo3);

	return 0;
}


void push(int *topo, int valor, int P[]){
	if(*topo < TAM){
		P[*topo] = valor;
		(*topo)++;
	}
	else{
		printf("Lista cheia!\n");
	}
}

void imprimir_pilha(int P[], int topo){
	for(int i = 0; i < topo; i++){
		printf("P[%i] = %i\n", i, P[i]);
	}
}

void push_ordenado_P3(int P1[], int P2[], int P3[], int *topo1, int *topo2, int *topo3){
	int vetor[TAM], j = 0;

	for(int i = *topo1; i > 0; i--)
		push(topo3, pop(topo1, P1), P3);

	for(int i = *topo2; i > 0; i--)
		push(topo3, pop(topo2, P2), P3);

	for(int i = *topo3; i > 0; i--){
		vetor[j] = pop(topo3, P3);
		j++;
	}
	int posicao = 0, aux;

	for(int i = 0; i < j - 1; i++){
		int maior = vetor[i];
		for(int y = i + 1; y < j; y++){
			if(vetor[y] > maior){
				maior = vetor[y];
				posicao = y;
			}
		}
		if(maior != vetor[i]){
			aux = vetor[i];
			vetor[i] = vetor[posicao];
			vetor[posicao] = aux;
		}
	}

	for(int i = 0; i < j; i++){
		push(topo3, vetor[i], P3);
	}


}


int pop(int *topo, int P[]){
	int removido;

	if(*topo >= 0){
		removido = P[*topo - 1];
		P[*topo - 1] = 0;
		(*topo)--;
	}
	else{
		printf("Pilha vazia");
	}

	return removido;
}
