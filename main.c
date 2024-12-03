#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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
    
    // Gera a posição aleatória para o zero
    int zero_pos = rand() % (linhas * colunas);
    
    // Gera a posição aleatória para o número 3
    int tres_pos;
    do {
        tres_pos = rand() % (linhas * colunas);
    } while (tres_pos == zero_pos);
    
    // Gera o labirinto
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int pos = i * colunas + j;
            if (pos == zero_pos) {
                fputc('0', arquivo);
            } else if (pos == tres_pos) {
                fputc('3', arquivo);
            } else {
                // Gera um número aleatório entre 1 e 2
                char celula = '1' + rand() % 2;
                fputc(celula, arquivo);
            }
        }
        fputc('\n', arquivo); // Quebra de linha
    }
    
    // Fecha o arquivo
    fclose(arquivo);
    printf("Labirinto salvo no arquivo '%s'.\n", arquivo_saida);
}

int main() {
    // Configuração do labirinto
    int linhas = 10;        // Número de linhas
    int colunas = 10;       // Número de colunas
    int num_chaves = 1;     // Número de chaves iniciais
    const char *arquivo_saida = "labirinto.txt"; // Nome do arquivo de saída
    
    // Gera e salva o labirinto
    gerar_labirinto(linhas, colunas, num_chaves, arquivo_saida);
    
    return 0;
}