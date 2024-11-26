#include "Labirinto.h"
#include <string.h>

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

                default:
                    break;
            }
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
            printf("Cor: %s\n", tabuleiro[i][j].cor);
            printf("Número: %d\n", tabuleiro[i][j].numero);
            printf("Começo: %s\n", tabuleiro[i][j].isstart ? "Sim" : "Não");
            printf("Chave: %s\n", tabuleiro[i][j].iskey ? "Sim" : "Não");
            printf("Porta: %s\n", tabuleiro[i][j].isdoor ? "Sim" : "Não");
            printf("Parede: %s\n", tabuleiro[i][j].iswall ? "Sim" : "Não");
            printf("--------------------\n");
        }
    }
}