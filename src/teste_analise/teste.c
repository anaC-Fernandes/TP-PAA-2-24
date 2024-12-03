#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int func(int depth,int n, int max, int* recMax, int* recNum){
  char marker;
  depth += n;
  printf("%d --- %d\r\n", n,depth);
 
  //Backtracking deve receber o ponteiro para os dois inteiros recMax e recNum
  //Esse if deve ir dentro do backtracking
  #ifdef ANALISE  
    #if ANALISE == 1
      *recNum = *recNum + 1;
      if(n > *recMax){
        *recMax = n;
      }
    #endif
  #endif
  //Ate aqui so

  if (n>max)
    return depth;

  return func(depth,n+1,max, recMax, recNum);
}


int main()
{
  int recMax=0,recNum=0;
  int depth;

  //Backtracking deve receber os enderecos de memoria dos inteiros para contagem, &recMax e %recNum
  depth = func(0,0,15, &recMax, &recNum);
  depth = func(0,0,12, &recMax, &recNum);
  printf("Profundidade: %d\n", depth);
  
  //Esse if deve ir ao final da main, para imprimir se Analise for 1
  #ifdef ANALISE  
    #if ANALISE == 1
      printf("Iteracoes: %d, Max: %d", recNum, recMax);
    #endif
  #endif
  //Ate aqui so

  return 0;
}