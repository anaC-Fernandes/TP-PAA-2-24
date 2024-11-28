#include "Labirinto.c"
#include "Menus.c"

int main() {
    int escolha = menu_principal();
    FILE* arquivo;
    if (escolha == 1) {
        arquivo = menu_arquivo();
    }
    int dimensoes[3];
    get_dimensões(arquivo, dimensoes);
    int linhas = dimensoes[0];
    int colunas = dimensoes[1];
    labirinto tabuleiro = Alocar_Labirinto(linhas, colunas);
    Preencher_Labirinto(&tabuleiro, linhas, colunas, arquivo);
    //Imprimir_Labirinto(tabuleiro, linhas, colunas);

    char** desenho = malloc((linhas + 2) * sizeof(char*));
    for (int i = 0; i < linhas + 2; i++) {
        desenho[i] = malloc((colunas + 2) * sizeof(char));
    }

    Alocar_Labirinto_Grafico(desenho, linhas, colunas, tabuleiro);
    printf("\033[2J\033[1;1H"); //Limpa a tela 
    Grafico_Labirinto(desenho, linhas, colunas);
    //Imprimir_Labirinto_Grafico(desenho, linhas, colunas);
    Destrutor_Labirinto(tabuleiro, linhas);
    fclose(arquivo);
    return 0;
}