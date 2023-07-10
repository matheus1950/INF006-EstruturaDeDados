#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct no{
	int valor;
	int altura;
	struct no* esquerda, *direita;
}No;


void freeArv(No *raiz);

No* inserir(No* raiz, int numero, FILE* escrita,int alt);
void imprime_inOrdem(No *raiz, FILE* escrita);
int soma(No *raiz);

int main() {

    FILE* leitura;
    FILE* escrita;

    leitura = fopen("L2Q2.in", "r");
    escrita = fopen("L2Q2.out", "w");

    if(leitura){

		while(!feof(leitura)){
			char lido[255];
			int num;

			fgets(lido, 255, leitura);

			char *tok = strtok(lido, " ");

			No* raiz = NULL;

			while(tok){
				num = atoi(tok);

				raiz = inserir(raiz, num, escrita,0); //só o primeiro é a raiz

				tok = strtok(NULL, " ");
			}//fim loop tok

      imprime_inOrdem(raiz,escrita);
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


No* inserir(No* raiz, int numero, FILE* escrita,int alt){
	if(raiz == NULL){
		No* aux = (No*)malloc(sizeof(No));
		if(aux){
			aux->valor = numero;
      aux->altura = alt;
			aux->esquerda = NULL;
			aux->direita = NULL;

			return aux;
		}
		else
			printf("Não foi possível alocar memória\n");
	}
	else{

		if(numero < raiz->valor){
      alt++;
			raiz->esquerda = inserir(raiz->esquerda, numero, escrita,alt);
    }
		else if(numero > raiz->valor){
      
			raiz->direita = inserir(raiz->direita, numero, escrita,alt);
    }
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
void imprime_inOrdem(No *raiz, FILE* escrita){
  int resultado=0;
  if(raiz->direita != NULL || raiz->esquerda != NULL){
    if(raiz->esquerda)
    imprime_inOrdem(raiz->esquerda,escrita);
    
    if(raiz->direita != NULL && raiz->esquerda != NULL){
      resultado=soma(raiz->direita)-soma(raiz->esquerda);
    }
    else if(raiz->direita != NULL && raiz->esquerda == NULL){
      resultado+=soma(raiz->direita);
    }
    else if(raiz->direita == NULL && raiz->esquerda != NULL){
      resultado-=soma(raiz->esquerda);
    }
    
    fprintf(escrita,"%d(%d) ",raiz->valor,resultado);
    
    if(raiz->direita)
    imprime_inOrdem(raiz->direita,escrita);
  }
  else if(raiz->direita == NULL && raiz->esquerda == NULL){
     fprintf(escrita,"%d(0) ",raiz->valor);
  }
}
int soma(No *raiz){
  int res = raiz->valor;

  if(raiz->direita != NULL || raiz->esquerda != NULL){

    if(raiz->esquerda){
    No * esquerda =raiz->esquerda;
    res+=soma(esquerda);
    }
    if(raiz->direita){
    No * direita =raiz->direita;
    res += soma(direita);
    }
    
  }
  return res;
}
