#include "Labirinto.c"

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
            else if (tabuleiro[i][j].isvisited){
                desenho[i + 1][j + 1] = 'v'; // Visitado
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
            
            case 'v':
                printf("██");  // Símbolo de visitado
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
    Grafico_Labirinto(desenho, linhas, colunas);
    
    printf("Pressione a tecla enter para voltar ao menu...\n");
    while (getchar() != '\n'); // Limpa o buffer
    getchar(); // Aguarda uma tecla
    for (int i = 0; i < linhas + 2; i++) {
        free(desenho[i]);
    }
    free(desenho);
}