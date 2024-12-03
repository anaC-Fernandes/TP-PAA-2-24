//
// Created by gabri on 02/12/2024.
//
#include "Estudante.h"
#include <string.h>
void imprime_labirinto(labirinto lab, ordem_matriz ordem, estudante aluno) {
    for (int i = 0; i < ordem.linhas; i++) {
        for (int j = 0; j < ordem.colunas; j++) {
            if (i == aluno.linha_atual && j == aluno.coluna_atual) {
                printf("E "); // Estudante
            } else if (lab[i][j].iswall) {
                printf("# "); // Parede
            } else if (lab[i][j].isdoor) {
                printf("D "); // Porta
            } else if (lab[i][j].iskey) {
                printf("K "); // Chave
            } else {
                printf(". "); // Caminho livre
            }
        }
        printf("\n");
    }
    printf("\n");
}
int main() {
    FILE *arquivo = fopen("C:\\Users\\gabri\\OneDrive\\Documentos\\GitHub\\TP-PAA-2-24\\lib\\labirinto.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    ordem_matriz ordem;
    int dimensoes[2];
    labirinto tabuleiro = Processar_Arquivo(arquivo, dimensoes, &ordem);
    fclose(arquivo);

    estudante *aluno = criaEstudante(0, 8 , 4);
    Movimenta_estudante(tabuleiro, aluno, ordem);

    printf("Quantidade de movimentos: %d\n", aluno->qtde_movimentos);
    printf("Estudante chegou a primeira linha na coluna %d\n", aluno->coluna_atual);
    imprime_labirinto(tabuleiro, ordem, *aluno);
    Destrutor_Labirinto(tabuleiro, ordem.linhas);
    free(aluno);

    return 0;
}




FILE* menu_arquivo(){
    char caminho [256];

    strcpy(caminho, "C:\\Users\\gabri\\OneDrive\\Documentos\\GitHub\\TP-PAA-2-24\\lib\\labirinto.txt");
    FILE* arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }
    return arquivo;
}