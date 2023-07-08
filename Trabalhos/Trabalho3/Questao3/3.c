#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no{
	int valor;
	int altura;
	struct no* esquerda, *direita;
}No;

No* inserir(No* raiz, int numero);
void freeArv(No *raiz);
void imprimeOrdem(No *raiz, FILE* escrita, int altura, int ultimo);
No* remover(No* raiz, int numero);
int ultimoValor(No *raiz);

int main() {

    FILE* leitura;
    FILE* escrita;

    leitura = fopen("L2Q3.in", "r");
    escrita = fopen("L2Q3.out", "w");

    if(leitura){

		while(!feof(leitura)){
			char lido[255], aR;
			int num, altura = 0;

			fgets(lido, 255, leitura);

			char *tok = strtok(lido, " ");

			No* raiz = NULL;

			while(tok){
				if(strcmp(tok, "a") == 0 || strcmp(tok, "r") == 0){
					sscanf(tok, "%c", &aR);

					tok = strtok(NULL, " ");

					sscanf(tok, "%d", &num);

					if(aR == 'a')
						raiz = inserir(raiz, num);
					else if(aR == 'r')
						raiz = remover(raiz, num);
				}

				tok = strtok(NULL, " ");
			}//fim loop tok

			int ultimo = ultimoValor(raiz);
			imprimeOrdem(raiz, escrita, altura, ultimo);

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
No* inserir(No* raiz, int numero){
	if(raiz == NULL){
		No* aux = (No*)malloc(sizeof(No));
		if(aux){
			aux->valor = numero;
			aux->esquerda = NULL;
			aux->direita = NULL;

			return aux;
		}
		else
			printf("Não foi possível alocar memória\n");
	}
	else{

		if(numero < raiz->valor)
			raiz->esquerda = inserir(raiz->esquerda, numero);
		else
			raiz->direita = inserir(raiz->direita, numero);
	}

	return raiz;
}

void freeArv(No *raiz){

	if(raiz != NULL){
		freeArv(raiz->esquerda);
		freeArv(raiz->direita);
		free(raiz);
	}
}

No* remover(No* raiz, int numero){
	if(raiz == NULL){
		return inserir(raiz, numero); //se o número não existe, será inserido!
	}
	else{
		if(raiz->valor == numero){
			if(raiz->esquerda == NULL && raiz->direita == NULL){ //remove nós sem filhos
				free(raiz);
				return NULL;
			}
			else if((raiz->esquerda == NULL && raiz->direita != NULL) || (raiz->esquerda != NULL && raiz->direita == NULL)){ //remove nós de apenas 1 filho(ou direita ou esquerda) - a operação entre parenteses tem o intuito de substituir o "ou exclusivo", que não está presente em C
				No*	aux;
				if(raiz->esquerda != NULL)
					aux = raiz->esquerda;
				else
					aux = raiz->direita;

				free(raiz);
				return aux;
			}
			else{
				No* aux = raiz->direita;
				while(aux->esquerda != NULL)
					aux = aux->esquerda;
				raiz->valor = aux->valor;
				aux->valor = numero;
				raiz->direita = remover(raiz->direita, numero);

				return raiz;
			}
		}
		else{
			if(numero < raiz->valor)
				raiz->esquerda = remover(raiz->esquerda, numero);
			else
				raiz->direita = remover(raiz->direita, numero);
		}
		return raiz;
	}
}

void imprimeOrdem(No *raiz, FILE* escrita, int altura, int ultimo){

    if(raiz != NULL){

        imprimeOrdem(raiz->esquerda, escrita, altura + 1, ultimo);
        if(raiz->valor != ultimo)
        	fprintf(escrita, "%d (%d) ", raiz->valor, altura);
        else
        	fprintf(escrita, "%d (%d)", raiz->valor, altura);
        imprimeOrdem(raiz->direita, escrita, altura + 1, ultimo);
    }
}

int ultimoValor(No *raiz){ //para identificar o último elemento e não dar espaço após ele

		if(raiz!= NULL){
			No* aux = raiz;
			while(aux->direita)
				aux = aux->direita;
			return aux->valor;
		}
		else
			return 1;
}
