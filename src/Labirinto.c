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

void Alocar_Labirinto_Grafico(char** desenho, int linhas, int colunas, labirinto tabuleiro) {
    // Construir a moldura
    for (int i = 0; i < linhas + 2; i++) {
        for (int j = 0; j < colunas + 2; j++) {
            if ((j == 0 || j == colunas + 1) && (i > 0 && i < linhas + 1)) {
                desenho[i][j] = '|'; // Bordas verticais
            } 
            else if ((i == 0 || i == linhas + 1) && (j > 0 && j < colunas + 1)) {
                desenho[i][j] = '='; // Bordas horizontais
            } 
            else if (i == 0 && j == 0) {
                desenho[i][j] = '+'; // Canto superior esquerdo
            } 
            else if (i == 0 && j == colunas + 1) {
                desenho[i][j] = 'y'; // Canto superior direito
            } 
            else if (i == linhas + 1 && j == 0) {
                desenho[i][j] = 'z'; // Canto inferior esquerdo
            } 
            else if (i == linhas + 1 && j == colunas + 1) {
                desenho[i][j] = 'x'; // Canto inferior direito
            } 
            else {
                desenho[i][j] = ' '; // Espaço vazio
            }
        }
    }

    // Preencher o conteúdo interno do labirinto
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (strcmp(tabuleiro[i][j].cor, "Verde") == 0) {
                desenho[i + 1][j + 1] = '0';
            } 
            else if (strcmp(tabuleiro[i][j].cor, "Branco") == 0) {
                desenho[i + 1][j + 1] = '1';
            } 
            else if (strcmp(tabuleiro[i][j].cor, "Azul") == 0) {
                desenho[i + 1][j + 1] = '2';
            } 
            else if (strcmp(tabuleiro[i][j].cor, "Vermelho") == 0) {
                desenho[i + 1][j + 1] = '3';
            } 
            else if (strcmp(tabuleiro[i][j].cor, "Amarelo") == 0) {
                desenho[i + 1][j + 1] = '4';
            } 
            else {
                desenho[i + 1][j + 1] = ' '; // Espaço vazio para células não reconhecidas
            }
        }
    }
}

void Imprimir_Labirinto_Grafico_Teste(char** desenho, int linhas, int colunas) {
    for (int i = 0; i < linhas + 2; i++) {
        for (int j = 0; j < colunas + 2; j++) {
            printf("%c", desenho[i][j]);
        }
        printf("\n");
    }
}

void Grafico_Labirinto(char** grafico, int linhas, int colunas) {
    printf("\033[2J\033[1;1H"); //Limpa a tela
    for (int i = 0; i < linhas+2; i++) {
        for (int j = 0; j < colunas+2; j++) {
            switch (grafico[i][j]) {
            case '0':
                printf("\033[1;32m");  // Cor verde
                printf("██");  // Quadrado cheio em verde
                printf("\033[0m");  // Resetando a cor
                break;
            
            case '1':
                printf("  ");  // Espaço em branco
                break;

            case '2':
                printf("\033[1;34m");  // Cor azul
                printf("██");  // Quadrado cheio em azul
                printf("\033[0m");  // Resetando a cor
                break;

            case '3':
                printf("\033[1;31m");  // Cor vermelha
                printf("██"); // Quadrado cheio em vermelho
                printf("\033[0m");  // Resetando a cor
                break;

            case '4':
                printf("cc");  // Símbolo de chave
                break;
            
            case '|':
                if (j == 0){
                    printf("║ ");
                } else {
                    printf(" ║");
                }
                break;
            
            case '=':
                printf("══");
                break;
            
            case '+':
                printf("╔═");
                break;

            case 'x':
                printf("═╝");
                break;

            case 'z':
                printf("╚═");
                break;
            
            case 'y':
                printf("═╗");
                break;
            
            default:
                printf("Erro");
                break;
            }
        }
        printf("\n");
    }
}

void Labirinto_Gráfico(int linhas,int colunas,labirinto tabuleiro) {
    char** desenho = malloc((linhas + 2) * sizeof(char*));
    for (int i = 0; i < linhas + 2; i++) {
        desenho[i] = malloc((colunas + 2) * sizeof(char));
    }
    Alocar_Labirinto_Grafico(desenho, linhas, colunas, tabuleiro);
    Imprimir_Labirinto_Grafico_Teste(desenho, linhas, colunas);
    Grafico_Labirinto(desenho, linhas, colunas);
    for (int i = 0; i < linhas + 2; i++) {
        free(desenho[i]);
    }
    free(desenho);
}
