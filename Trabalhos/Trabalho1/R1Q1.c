#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_TAM 255
#define LINHA 20
#define COLUNA 10
int main(void) {

  FILE *Leitura = fopen("L1Q1.in", "r");
  FILE *Escrita = fopen("L1Q1.out", "w");
  char lido[MAX_TAM];
  int matriz [LINHA][COLUNA];
  
  if(Leitura){
    printf("Arquivo de leitura encontrado\n");
    while(!feof(Leitura)){
      int linha = -1, coluna = 0,colTam[LINHA]={0};
      
      fgets(lido, 255, Leitura);
    	printf("# Lido: %s\n\n", lido);

    	char *tok = strtok(lido, " ");
      
      while(tok){
        printf("tok : %s\n", tok);
        if(strcmp(tok, "start")){//significa que após um start
    
          matriz[linha][coluna] = atoi(tok);
          printf("matriz[%i][%i] = %i\n\n", linha, coluna, matriz[linha][coluna]);
          colTam[linha]++;
          coluna++;
        }
        else{
        	linha++;
          coluna = 0;
        }
        tok = strtok(NULL, " ");
      }
      //acho que é aqui que você vai colocar as ordenações e etc, porque a matriz já vai estar toda preenchida
      int somas[LINHA] = {0};
      int ordem[LINHA] ={0};
      for(int i=0;i<=linha;i++){
        int col = colTam[i];//linha
        for(int j =0;j <col;j++){
          somas[i] += matriz[i][j];
          }
          ordem[i] += i; 
        }
      for(int i=0;i<=linha;i++){
        int auxs = somas[i];
        int auxO = ordem[i];
        int j = i-1;
        while(j>=0 && somas[j]>auxs){
          somas[j+1] = somas[j];
          ordem[j+1] = ordem[j];
          j-=1;
        }//acho q esqueci de diminuir o valor de J
        somas[j+1]= auxs;
        ordem[j+1]= auxO;
      }
      for(int i =0;i<=linha;i++){
        int col = colTam[i];
        for(int j=0;j<col;j++){
          int aux= matriz[i][j];
          int k =j-1;
          while(k>=0 && matriz[i][k]>aux){
            matriz[i][k+1]= matriz[i][k];
            k-=1;
          }
          matriz[i][k+1]=aux;
        }
      }
      if(Escrita){
        //fgets("start", 255, Escrita);
        for(int i =0;i<=linha;i++){
          int lin = ordem[i];
          int col = colTam[lin];
          fprintf(Escrita,"start ");
          for(int j=0;j<col;j++){
           fprintf(Escrita,"%d ",matriz[lin][j]); 
          }
          if(!feof(Leitura) && i==linha){
            fprintf(Escrita,"\n");
          }
        }
      }
      else{
        printf("Não foi possível criar o arquivo de saída");
        return 1;
      }
    }
  }
  fclose(Leitura);
  fclose(Escrita);
  return 0;
}


//if(Escrita){
//  fgets("start", 255, Escrita);
//  while(){
//    
//  }
//  
//}
//else{
//  printf("Não foi possível criar o arquivo de saída");
//  return 1;
//}
//