#include "Labirinto.c"

int main() {
    char caminho [256];
    //printf("Digite o caminho do arquivo: ");
    //scanf("%s", caminho);
    strcpy(caminho, "/home/Lucas/Documentos/Codes/C/Trabalhos/TP-PAA-2-24/lib/labirinto.txt");
    FILE* arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    int dimensoes[3];
    get_dimensões(arquivo, dimensoes);
    int linhas = dimensoes[0];
    int colunas = dimensoes[1];
    labirinto tabuleiro = Alocar_Labirinto(linhas, colunas);
    Preencher_Labirinto(&tabuleiro, linhas, colunas, arquivo);
    Imprimir_Labirinto(tabuleiro, linhas, colunas);
    Destrutor_Labirinto(tabuleiro, linhas);
    fclose(arquivo);
    return 0;
}