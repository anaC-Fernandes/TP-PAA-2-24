#include <stdlib.h>
#include <string.h>

#include <stdio.h>


#include "Labirinto.h"

void get_dimensoes(FILE* arquivo, int* dimensoes) {
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
    get_dimensoes(arquivo, dimensoes);
    int linhas = dimensoes[0];
    int colunas = dimensoes[1];
    ordem->colunas = colunas;
    ordem->linhas = linhas;
    labirinto tabuleiro = Alocar_Labirinto(linhas, colunas);
    Preencher_Labirinto(&tabuleiro, linhas, colunas, arquivo);
    return tabuleiro;
}
void print_matriz(labirinto tabuleiro, int linhas, int colunas){
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d ", tabuleiro[i][j].numero);
        }
        printf("\n");
    }
}

///////////// EXTRA GERADOR DE LABIRINTO /////////////
void gerar_labirinto(int linhas, int colunas, int num_chaves, const char *arquivo_saida) {
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Abre o arquivo para escrita
    FILE *arquivo = fopen(arquivo_saida, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve o cabeçalho
    fprintf(arquivo, "%d %d %d\n", linhas, colunas, num_chaves);

    // Cria uma matriz para o labirinto
    char** labirinto = (char**)malloc(linhas * sizeof(char*));
    for (int i = 0; i < linhas; i++) {
        labirinto[i] = (char*)malloc(colunas * sizeof(char));
        for (int j = 0; j < colunas; j++) {
            labirinto[i][j] = '2'; // Inicializa todas as células como '2' (parede)
        }
    }

    // Define a posição inicial do estudante
    int x = linhas - 1; // Última linha
    int y = rand() % colunas; // Coluna aleatória
    labirinto[x][y] = '0'; // Marca a posição inicial do estudante

    // Cria o caminho até a primeira linha
    while (x > 0) {
        if (labirinto[x][y] != '0') {
            labirinto[x][y] = '1'; // Marca o caminho como célula transitável
        }

        // Escolhe uma direção: 0 = cima, 1 = esquerda, 2 = direita
        int direction = rand() % 3;
        if (direction == 0 && x > 0) { // Cima
            x--;
        } else if (direction == 1 && y > 0) { // Esquerda
            y--;
        } else if (direction == 2 && y < colunas - 1) { // Direita
            y++;
        }
    }
    labirinto[0][y] = '1'; // Garante que a célula na primeira linha seja parte do caminho

    // Insere um `3` no caminho, se permitido
    if (num_chaves > 0) {
        int inserir_tres = rand() % 2; // 50% de chance de inserir o `3`
        if (inserir_tres) {
            int tres_x, tres_y;
            do {
                tres_x = rand() % linhas;
                tres_y = rand() % colunas;
            } while (labirinto[tres_x][tres_y] != '1'); // Garante que o `3` está no caminho
            labirinto[tres_x][tres_y] = '3';
        }
    }

    // Preenche o restante do labirinto aleatoriamente
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (labirinto[i][j] == '2') { // Apenas paredes podem ser modificadas
                labirinto[i][j] = (rand() % 2) ? '1' : '2'; // Caminho ou parede
            }
        }
    }

    // Escreve o labirinto no arquivo
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            fputc(labirinto[i][j], arquivo);
        }
        fputc('\n', arquivo); // Quebra de linha
    }

    // Libera a memória alocada para o labirinto
    for (int i = 0; i < linhas; i++) {
        free(labirinto[i]);
    }
    free(labirinto);

    // Fecha o arquivo
    fclose(arquivo);
    printf("Labirinto salvo no arquivo '%s'.\n", arquivo_saida);
}
