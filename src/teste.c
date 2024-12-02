//
// Created by gabri on 02/12/2024.
//
#include "Estudante.h"
#include <string.h>
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
    Imprimir_Labirinto(tabuleiro, ordem.linhas, ordem.colunas);
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