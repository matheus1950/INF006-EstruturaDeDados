#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int num;
	struct No *prox;
}no;

void inserir_inicio(no **inicio, int valor);
void inserir_fim(no **inicio, int valor);
void imprimir(no *inicio);

int main(){
no *inicio = NULL;

inserir_inicio(&inicio, 8);

printf("%i\n", inicio->num);

inserir_fim(&inicio, 2);

imprimir(inicio);
}

void inserir_inicio(no **inicio, int valor){
	no* novo = malloc(sizeof(no));

	novo->num = valor;

	if(novo){
		if(*inicio == NULL){
			novo->prox = NULL;
			*inicio = novo;
		}
		else{
			novo->prox = *inicio;
			*inicio = novo;
		}
	}

	else{
		printf("Não foi possível alocar");
	}

}

void inserir_fim(no **inicio, int valor){
	no *novo = malloc(sizeof(no)), *aux = *inicio;
	novo->num = valor;
	novo->prox = NULL;

	if(novo){
		if(*inicio == NULL)
			*inicio = novo;
		else{
			while(aux->prox != NULL){
				aux = aux->prox;
			}
			aux->prox = novo;
		}
	}

}

void imprimir(no *inicio){
	no *aux = inicio;

	if(aux){
		do{
			printf("Lista valor : %i\n", aux->num);
			aux = aux->prox;
		}while(aux != NULL);
	}
}
