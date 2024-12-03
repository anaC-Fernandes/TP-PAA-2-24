

#ifndef DESENHO_H
#define DESENHO_H
#include "Estudante.c"


void Alocar_Labirinto_Grafico(char** desenho, int linhas, int colunas, labirinto tabuleiro);
void Imprimir_Labirinto_Grafico_Teste(char** desenho, int linhas, int colunas);
void Grafico_Labirinto(char** grafico, int linhas, int colunas);
void Labirinto_Grafico(int linhas,int colunas,labirinto tabuleiro);

#endif //DESENHO_H
