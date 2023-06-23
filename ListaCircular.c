#include <stdio.h>
#include <stdlib.h>

typedef struct No{
	int num;
	struct No *prox;
}no;

typedef struct Circular{
	int tam;
	no *inicio;
	no *fim;
}circular;

void criar_lista(circular *lista);
void inserir_no_fim(circular *lista, int valor);
void imprimir(circular *lista);
void inserir_no_inicio(circular *lista, int valor);
no* remover(circular *lista, int num);
void finalizar_limpandoLista(circular *lista);

int main(){
	circular listaCircular;
	//testes
	criar_lista(&listaCircular);

	inserir_no_fim(&listaCircular, 8);
	inserir_no_fim(&listaCircular, 9);
	inserir_no_fim(&listaCircular, 12);

	inserir_no_inicio(&listaCircular, 4);
	inserir_no_inicio(&listaCircular, 3);
	inserir_no_inicio(&listaCircular, 2);

	imprimir(&listaCircular);

	free(remover(&listaCircular, 12));
	free(remover(&listaCircular, 9));

	imprimir(&listaCircular);

	free(remover(&listaCircular, 8));
	imprimir(&listaCircular);

	//finalizar_limpandoLista(&listaCircular);
}

void criar_lista(circular *lista){
	lista->inicio = NULL;
	lista->fim = NULL;
}

void inserir_no_fim(circular *lista, int valor){
	no *novo = (no*)malloc(sizeof(no));

	if(novo){
		novo->num = valor;

		if(lista->inicio == NULL){
			lista->inicio = novo; //ambos devem apontar para o novo espaço alocado
			lista->fim = novo;
			lista->fim->prox = lista->inicio; //lista circular
		}
		else{
			lista->fim->prox = novo; //antes apontava para o inicio, agora apontará para o novo final. Tenho que fazer isso para o nó referenciado por lista->fim agore aponte para novo, assim, na linha de baixo poderei utilizar lista->fim para apontar para o meu novo endereço(novo).
			lista->fim = novo; //dizer que é o novo final
			lista->fim->prox = lista->inicio; //circular
		}
		lista->tam++;
	}
	else{
		printf("Memoria não alocada!\n");
	}
}

void inserir_no_inicio(circular *lista, int valor){
    no *novo = (no*)malloc(sizeof(no));

    if(novo){
        novo->num = valor;
        novo->prox = lista->inicio; //se tinha algum nó na lista->inicio, agora irá para o novo->proximo, deixando a lista->inicio passível de modificação
        lista->inicio = novo;

        if(lista->fim == NULL) //se não houver nada ao fim, novo será o fim(assim com o inicio);
            lista->fim = novo;

        lista->fim->prox = lista->inicio;
        lista->tam++;
    }
    else{
        printf("Erro ao alocar memória!\n");
    }
}

void imprimir(circular *listaCircular){
	no *aux = listaCircular->inicio;
	if(aux){
		do{
			printf("Valor lista - do inicio ao fim: %i\n", aux->num);
			aux = aux->prox;
		}while(aux != listaCircular->inicio); //imprimir a lista até que ela retorne ao inicio
	}
	else{
		printf("Ainda não existe uma lista");
	}
}

no* remover(circular *lista, int num){ //para remover um nó a partir de seu valor
	no *aux, *remover = NULL;

	if(lista->inicio){
		if(lista->inicio->num == num){ //está no início??
			if(lista->inicio == lista->fim){ //o início é igual ao fim?
				printf("Entrou 1\n");
				remover = lista->inicio;
				lista->inicio = NULL;
				lista->fim = NULL;
				lista->tam--;
			}
			else{ //o início não é igual ao fim!
				remover = lista->inicio;
				lista->inicio = remover->prox;
				printf("novo valor de inicio: %i\n", lista->inicio->num);
				lista->fim->prox = lista->inicio;
				lista->tam--;
			}
		}
		else{ //não está no início
			aux = lista->inicio;
			while(aux->prox != lista->inicio && aux->prox->num != num){ //parar se o número for encontrado ou não existir
				aux = aux->prox;
			}
			if(aux->prox->num == num){
				if(lista->fim == aux->prox){ //o número foi encontrado ao final da lista?
					remover = aux->prox;
					aux->prox = remover->prox; //não daria o mesmo de apontar para lista->inicio? já que o próximo de aux->prox(final) é o inicio??
					lista->fim = aux;
					printf("Entrou 2\n");
				}

				else{ //o número não está no final
					remover = aux->prox;
					aux->prox = remover->prox;
					printf("Entrou 3\n");
				}
			}
			lista->tam--;
		}
	}
	printf("endereço : %p\n", remover);
	return remover;
}

void finalizar_limpandoLista(circular *lista){
	no *atual = lista->inicio;
	no *anterior = lista->inicio;

	do{
		anterior = atual->prox;
		atual = anterior->prox;

		free(anterior);

	}while(atual != lista->inicio);

	lista->inicio = NULL;
	lista->fim = NULL;
}

