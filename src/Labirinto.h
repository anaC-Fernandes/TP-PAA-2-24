#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct cell {
    char cor[16];
    int numero;
    bool iswall;    // eParede
    bool isstart;   // eComeço
    bool isdoor;     // ePorta
    bool iskey;     // eChave
    bool isvisited; // eVisitado
} celula;

typedef celula** labirinto;

labirinto Alocar_Labirinto(int linhas, int colunas);
void Preencher_Labirinto(labirinto* tabuleiro, int linhas, int colunas, FILE *arquivo);
void Destrutor_Labirinto(labirinto tabuleiro, int linhas);
void Imprimir_Labirinto(labirinto tabuleiro, int linhas, int colunas);
