#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TAM 255
#define MAX 9
typedef struct pilha{
  char nome [30];
}pl;
int main(void) {
  FILE *Leitura = fopen("L1Q2.in", "r");
  FILE *Escrita = fopen("L1Q2.out", "w");
  char lido[MAX_TAM];
  if(Leitura){
    printf("Arquivo de leitura encontrado\n");
    
    while(!feof(Leitura)){
      pl pilha [10];
      pl aux[10];
      int top=-1;
      int auxTop=-1;
      fgets(lido, 255, Leitura);
      printf("# Lido: %s\n\n", lido);
      char *tok = strtok(lido, " ");
      
      while(tok){
        if(top < 10){
          printf("tok : %s\n", tok);
          if(top == -1){
            strcpy(pilha[++top].nome, tok);
            fprintf(Escrita,"push-%s ",tok);
          }
          else{
            int i=top;
            while(strcmp(tok,pilha[i].nome) <= 0 && i >- 1){
              i--;
            }
            if(i==top){
              strcpy(pilha[++top].nome, tok);
              fprintf(Escrita,"push-%s ",tok);
            }
            else if(i<top){
              int pop =0;
              while(top>i){
                strcpy(aux[++auxTop].nome, pilha[top--].nome);
                pop++;
              }
              fprintf(Escrita,"%dx-pop ",pop);
              strcpy(pilha[++top].nome, tok);
              fprintf(Escrita,"push-%s ",tok);
              while(auxTop>-1){
                strcpy(pilha[++top].nome, aux[auxTop--].nome);
                fprintf(Escrita,"push-%s ",pilha[top].nome);
              }
            }
          }
        }
        tok = strtok(NULL, " ");
      }
    }
  }
  fclose(Leitura);
  fclose(Escrita);
}
