#include <stdlib.h>
#include <string.h>

#include <stdio.h>


#include "Labirinto.h"

void get_dimensões(FILE* arquivo, int* dimensoes) {
    fscanf(arquivo, "%d %d %d", &dimensoes[0], &dimensoes[1], &dimensoes[2]);
}

labirinto Alocar_Labirinto(int linhas, int colunas) {
    labirinto tabuleiro = (labirinto)malloc(linhas * sizeof(celula*));
    for (int i = 0; i < linhas; i++) {
        tabuleiro[i] = (celula*)malloc(colunas * sizeof(celula));
    }
    return tabuleiro;
}

void Preencher_Labirinto(labirinto* tabuleiro,int linhas, int colunas, FILE *arquivo) {
    char linha_atual[colunas];
    fgets(linha_atual, colunas + 2, arquivo); // Pula a primeira linha
    for (int i = 0; i < linhas; i++) {
        fgets(linha_atual, colunas + 2, arquivo); // Inclui o '\n' e o '\0'
        for (int j = 0; j < colunas; j++) {
            switch (linha_atual[j]) {
                case '0':
                    strcpy((*tabuleiro)[i][j].cor, "Verde");
                    (*tabuleiro)[i][j].numero = 0;                
                    (*tabuleiro)[i][j].iswall = false;
                    (*tabuleiro)[i][j].isstart = true;
                    (*tabuleiro)[i][j].isdoor = false;
                    (*tabuleiro)[i][j].iskey = false;
                    break;

                case '1':
                    strcpy((*tabuleiro)[i][j].cor, "Branco");
                    (*tabuleiro)[i][j].numero = 1;
                    (*tabuleiro)[i][j].iswall = false;
                    (*tabuleiro)[i][j].isstart = false;
                    (*tabuleiro)[i][j].isdoor = false;
                    (*tabuleiro)[i][j].iskey = false;
                    break;

                case '2':
                    strcpy((*tabuleiro)[i][j].cor, "Azul");
                    (*tabuleiro)[i][j].numero = 2;
                    (*tabuleiro)[i][j].iswall = true;
                    (*tabuleiro)[i][j].isstart = false;
                    (*tabuleiro)[i][j].isdoor = false;
                    (*tabuleiro)[i][j].iskey = false;
                    break;

                case '3':
                    strcpy((*tabuleiro)[i][j].cor, "Vermelho");
                    (*tabuleiro)[i][j].numero = 3;
                    (*tabuleiro)[i][j].iswall = false;
                    (*tabuleiro)[i][j].isstart = false;
                    (*tabuleiro)[i][j].isdoor = true;
                    (*tabuleiro)[i][j].iskey = false;
                    break;

                case '4':
                    strcpy((*tabuleiro)[i][j].cor, "Amarelo");
                    (*tabuleiro)[i][j].numero = 4;
                    (*tabuleiro)[i][j].iswall = false;
                    (*tabuleiro)[i][j].isstart = false;
                    (*tabuleiro)[i][j].isdoor = false;
                    (*tabuleiro)[i][j].iskey = true;
                    break;

                default:
                    break;
            }
            (*tabuleiro)[i][j].isvisited = false;
        }
    }
}

void Destrutor_Labirinto(labirinto tabuleiro, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

void Imprimir_Labirinto(labirinto tabuleiro, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%c ", tabuleiro[i][j].numero);
        }
        printf("\n");
    }
}

labirinto Processar_Arquivo(FILE* arquivo, int* dimensoes, ordem_matriz *ordem) {
    get_dimensões(arquivo, dimensoes);
    int linhas = dimensoes[0];
    int colunas = dimensoes[1];
    ordem->colunas = colunas;
    ordem->linhas = linhas;
    labirinto tabuleiro = Alocar_Labirinto(linhas, colunas);
    Preencher_Labirinto(&tabuleiro, linhas, colunas, arquivo);
    return tabuleiro;
}
