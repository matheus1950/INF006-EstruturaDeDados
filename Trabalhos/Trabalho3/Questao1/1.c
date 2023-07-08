#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no{
	int valor;
	int altura;
	struct no* esquerda, *direita;
}No;

void freeArv(No *raiz);

No* inserir(No* raiz, int numero, FILE *escrita, int tamanho);

void maior(No* raiz, FILE* escrita);

int main() {

    FILE* leitura;
    FILE* escrita;

    leitura = fopen("L2Q1.in", "r");
    escrita = fopen("L2Q1.out", "w");

    if(leitura){

		while(!feof(leitura)){
			char lido[255];
			int num, tamanho = 0;

			fgets(lido, 255, leitura);

			char *tok = strtok(lido, " ");

			No* raiz = NULL;

			while(tok){
        num = atoi(tok);
  
        raiz = inserir(raiz, num, escrita, tamanho); //só o primeiro é a raiz
  
        tok = strtok(NULL, " ");
  
        fprintf(escrita, " "); //espaço apenas enquanto houver tok
			}//fim loop tok

			maior(raiz, escrita);

			if(!feof(leitura)) //quebra linha apenas enquanto houver linha para ler
				fprintf(escrita, "\n");


			freeArv(raiz);
    	 }

		fclose(leitura);
    } //fim de leitura

    else{
    	printf("Não foi possível ler o arquivo\n");
    	return 1;
    }

    fclose(escrita);

    return 0;
}


No* inserir(No* raiz, int numero, FILE* escrita, int tamanho){
	if(raiz == NULL){
		No* aux = (No*)malloc(sizeof(No));
		if(aux){
			aux->valor = numero;
			aux->esquerda = NULL;
			aux->direita = NULL;

			fprintf(escrita, "%d", tamanho); //imprime tamanho que começa em 0

			return aux;
		}
		else
			printf("Não foi possível alocar memória\n");
	}
	else{

		if(numero < raiz->valor)
			raiz->esquerda = inserir(raiz->esquerda, numero, escrita, tamanho + 1);
		else
			raiz->direita = inserir(raiz->direita, numero, escrita, tamanho + 1);
	}

	return raiz;
}

void maior(No *raiz, FILE* escrita){
	int tamanho = 0;

	if(raiz->direita != NULL){ //se não tiver nada à direita é a própria raiz!
		No* aux = raiz;
		No* pred; //predecessor
		while(aux->direita){
			tamanho++;
			pred = aux; //salvar o anterior
			aux = aux->direita;
		}
		fprintf(escrita, "max %d alt %d pred %d", aux->valor, tamanho, pred->valor);
	}
	else
		fprintf(escrita, "max %d alt 0 pred NaN", raiz->valor);
}

void freeArv(No *raiz){

	if(raiz != NULL){
		freeArv(raiz->esquerda);
		freeArv(raiz->direita);
		free(raiz);
	}
}


